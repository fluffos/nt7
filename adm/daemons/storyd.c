// storyd.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SAVE;

// 每 10 天刷新故事
#define REFRESH_INTERVAL        10 * 86400

string *story_name;
mapping history;
int     last_update = 0;

nosave mapping interval;
nosave object  running_story;
nosave int step;
int    filter_listener(object ob);

private void init_story();
private void ready_to_start();
private void go_on_process(object ob);

string query_save_file()
{
        return DATA_DIR "storyd";
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "故事精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "故事系统已经启动。");

        // 恢复故事发生状况
        restore();

        if (! arrayp(story_name))
                init_story();

        if (! mapp(history))
                history = ([ ]);

        interval = ([ ]);
        ready_to_start();
}

int query_next_update()
{
        return last_update + REFRESH_INTERVAL - time();
}

void init_story()
{
        CHANNEL_D->do_channel(this_object(), "sys", "故事系统更新所有故事。");
        story_name = get_dir(STORY_DIR + "*.c");
        story_name = map_array(story_name, (: $1[0..<3] :));

        last_update = time();
}

private void ready_to_start()
{
        int dp;

        // 保存当前故事状况
        save();

        if ((dp = time() - last_update) >= REFRESH_INTERVAL)
                init_story();
        else
        if (dp < 0)
                last_update = time();

        remove_call_out("start_story");
        remove_call_out("process_story");
        call_out("start_story", 3600 + random(600));
}

private void go_on_process(object ob)
{
        remove_call_out("start_story");
        remove_call_out("process_story");
        call_out("process_story", 1, ob);
}

int clean_up()
{
        return 1;
}

object query_running_story()
{
        return running_story;
}

varargs void start_story(string sname)
{
        string *all_story;
        string name;
        object ob;

        ready_to_start();

        /*
        if (VERSION_D->is_boot_synchronizing())
                // 正在启动中同步版本？那么不启动任何故事
                return;
        */

        CHANNEL_D->do_channel(this_object(), "sys", "故事系统开始选择故事。");

        if (sname)
                all_story = explode(sname, ",");
        else
                all_story = filter_array(story_name,
                                         (: time() - (int)history[$1] > (int)interval[$1] :));
        while (sizeof(all_story))
        {
                name = all_story[random(sizeof(all_story))];
                if (undefinedp(history[name]))
                        history += ([ name : 0 ]);
                else
                        history[name] = (int)time();

                CHANNEL_D->do_channel(this_object(), "sys",
                                      "故事系统选择了故事(" + name + ")。");

                all_story -= ({ name });
                if (ob = find_object(STORY_DIR + name))
                        destruct(ob);

                catch(ob = load_object(STORY_DIR + name));
                running_story = ob;

                if (objectp(ob))
                {
                        if (! (interval[name] = ob->interval()))
                                interval[name] = 1800;
                        step = 0;
                        go_on_process(ob);
                        break;
                }
        }
}

void remove_story(string story)
{
        story_name -= ({ story });
}

string *query_all_story()
{
        return story_name;
}

void process_story(object ob)
{
        mixed line;
        object *listeners;
        string prompt;

        go_on_process(ob);

        if (! objectp(ob))
        {
                ready_to_start();
                return;
        }

        line = ob->query_story_message(step);
        step++;

        prompt = ob->prompt();
        if (! prompt) prompt = HIG "【故事】" NOR;
        if (functionp(line)) catch(line = evaluate(line));
        if (stringp(line))
        {
                listeners = filter_array(users(), (: filter_listener :));
                message("story",  prompt + WHT + line + "\n" NOR, listeners);
        }

        if (intp(line) && ! line)
        {
                ready_to_start();
                destruct(ob);
        }
}

int filter_listener(object ob)
{
        if( query("env/no_story", ob))return 0;
        return 1;
}

void give_gift(string gift, int amount, string msg)
{
        object ob, pob;
        object env;
        mapping ips;
        string ip, *ks;

        ips = ([ ]);
        foreach (pob in all_interactive())
        {
                if( wizardp(pob) || !query("born", pob) || 
                    ! living(pob) || ! environment(pob) ||
                    pob->is_ghost() ||
                    environment(pob)->is_chat_room())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (sizeof(ips) >= 1)
        {
                // 需要三个以上的IP登录才给与奖品

                // 随即抽一个IP
                ks = keys(ips);
                ip = ks[random(sizeof(ks))];

                // 在该IP地址上随即抽取一个玩家
                pob = ips[ip][random(sizeof(ips[ip]))];

                env = environment(pob);
                while (env && env->is_character())
                        env = environment(env);

                if (! objectp(env)) return;

                tell_room(env, msg);
                while (amount-- > 0)
                {
                        ob = new(gift);
                        if( ob->is_task() )
                                set_temp("task", 2, ob);
                        ob->move(env);
                }
                CHANNEL_D->do_channel( this_object(),
                        "sys", sprintf(NOR WHT "赠品%s" NOR WHT "掉到了"
                                HIC "%s" NOR WHT "(%O" NOR WHT ")。" NOR,
                                ob->name(), env->short(), env));
        }
}

string query_info()
{
        string msg;
        int dp;

        dp = time() - last_update;
        if (dp < 0) dp = 0;

        dp = REFRESH_INTERVAL - dp;
        if (dp < 0)
                msg = "故事精灵马上刷新所有故事。\n";
        else
                msg = "故事精灵将在" + appromix_time(dp) + "后刷新所有故事。\n";

        return msg;
}
