// closed.c
// updated by Lonely

// #pragma optimize
// #pragma save_binary

#define CLOSED_CMD              "/cmds/skill/closed"
#define BREAKUP_CMD             "/cmds/skill/breakup"
#define ANIMAOUT_CMD            "/cmds/skill/animaout"
#define DEATH_CMD               "/cmds/skill/death"
#define XIULIAN_CMD             "/cmds/skill/xiulian"
#define UPGRADE_CMD             "/cmds/skill/upskill"
#define SCHEME_CMD              "/cmds/usr/scheme"
#define TRIGGER_CMD             "/cmds/usr/trigger"

inherit F_SAVE;

mapping closed_users = 0;

void load_all_users();

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(3);
}

void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

string query_save_file()
{
        return DATA_DIR "closed";
}

mapping query_closed_users()
{
        return closed_users;
}

void user_closed(object user)
{
        user->set_short_desc("盘膝而坐，正在瞑目闭关修炼。");
        set_temp("last_closing", time(), user);
        if (! closed_users)
                closed_users = ([ ]);
        if (undefinedp(closed_users[query("id", user)]))
                closed_users += ([ query("id", user) : query("startroom", user) ]);
        else
                closed_users[query("id", user)] = query("startroom", user);
        save();
        user->save();
        set_heart_beat(10 + random(10));
}

void user_opened(object user)
{
        delete("doing", user);
        user->set_short_desc(0);
        delete_temp("last_closing", user);
        if (mapp(closed_users))
        {
                map_delete(closed_users, query("id", user));
                if (! sizeof(closed_users))
                {
                        closed_users = 0;
                        set_heart_beat(0);
                }
        }

        save();
        delete("startroom", user);
        user->save();
}

void heart_beat()
{
        /*
        if (! VERSION_D->is_version_ok())
                return;
        */

        load_all_users();
}

void continue_doing(object user_ob)
{
        int res;

        switch( query("doing", user_ob) )
        {
        case "closed":
                res = CLOSED_CMD->continue_closing(user_ob);
                break;

        case "breakup":
                res = BREAKUP_CMD->continue_breaking(user_ob);
                break;

        case "scheme":
                res = SCHEME_CMD->continue_scheme(user_ob);
                break;

        case "trigger":
                res = TRIGGER_CMD->continue_trigger(user_ob);
                break;

        case "animaout":
                res = ANIMAOUT_CMD->continue_upgradeing(user_ob);
                break;

        case "death":
                res = DEATH_CMD->continue_outing(user_ob);
                break;

        case "invent":
                res = UPGRADE_CMD->continue_uping(user_ob);
                break;

        case "xiulian":
                res = XIULIAN_CMD->continue_mending(user_ob);
                break;

        default:
                // Aha? The user isn't closing now
                res = 0;
                return;
        }

        if (! res)
                user_opened(user_ob);
}

void load_all_users()
{
        string u;
        object login_ob;
        object user_ob;

        if (! mapp(closed_users))
                return;

        if (! LOGIN_D->can_login())
                return;

        set_heart_beat(10 + random(10));
        foreach (u in keys(closed_users))
        {
                if (! objectp(user_ob = LOGIN_D->find_body(u)))
                {
                        // load the user
                        login_ob = new(LOGIN_OB);
                        set("id", u, login_ob);
                        if (! login_ob->restore())
                        {
                                destruct(login_ob);
                                map_delete(closed_users, u);
                                log_file("log", sprintf("closed：没有玩家(%s)。\n", u));
                                continue;
                        }

                        user_ob = LOGIN_D->make_body(login_ob);
                        if (! user_ob)
                        {
                                destruct(login_ob);
                                map_delete(closed_users, u);
                                log_file("log", sprintf("closed：无法生成玩家(%s)。\n", u));
                                continue;
                        }

                        if (! user_ob->restore())
                        {
                                destruct(login_ob);
                                destruct(user_ob);
                                map_delete(closed_users, u);
                                log_file("log", sprintf("closed：无法读取玩家(%s)的档案。\n", u));
                                continue;
                        }

                        // Setup the user and move he to the closing room
                        catch(LOGIN_D->enter_world(login_ob, user_ob));
                        if (! stringp(query("doing", user_ob)) || ! environment(user_ob))
                        {
                                destruct(login_ob);
                                destruct(user_ob);
                                map_delete(closed_users, u);
                        }
                        continue;
                }

                if (query_heart_beat(user_ob))
                        // the user is doing now
                        continue;

                continue_doing(user_ob);

                // continue to examine next user
        }
}
