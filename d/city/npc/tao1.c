// 桃谷六仙    make joke by That. Nov.6.1997
#include <ansi.h>

inherit NPC;

string *rnd_say = ({
        "我们桃谷六仙，是名震天下的六大英雄。这里的人居然都假装不认识我们！",
        "为什麽令狐冲这小子还没来？又和那个小妖女混在一起了？",
        "有谁可以给我一些钱？夜猫子的一千两银子还我们的时候我再还给你吧！",
        "我想看看青城派的屁股向后平沙落雁式！",
        "可不可以告诉我哪里可以大便？下次见到不戒那个臭婆娘可不会这么大方了！",
        "方正这个老秃驴在这里不是方丈啦？真可怜．．．",
        "那个死冲虚牛鼻子为什么不来接我们？",
        "厦门的美眉听说很漂亮？",
        "风儿和仙子这两个小浑蛋干嘛去了？",
        "快打酒来！愣什么！",
        "快把老头子和祖千秋拉成一堆烂肉！",
        "岳不群就是伪君子．．．",
        "你是任盈盈？",
        "嗨..",
});

varargs void drool(string msg, string who);

void create()
{
//      string name,id;

        set_name("桃根仙", ({ "taogen xian", "gen" }) );
        set("title", "普通百姓");
        set("gender", "男性");
        set("age", 66);
        set("attitude", "friendly");
        set("combat_exp", 1000000);
        set("env/wimpy", 100);
        //set("chat_chance", 30);
        set("chat_msg", ({
                (: command("eat1") :),
                (: command("goeat") :),
                (: command("mapi1") :),
                (: command("drinkcup") :),
                (: command("ugly") :),
                (: command("mapi") :),
                (: command("slogan2") :),
                (: command("zzz") :),
                (: command("lazy") :),
                (: command("slogan") :),
                (: drool :),
                (: drool :),
                (: drool :),
                (: drool :),
                (: drool :),
                (: drool :),
        }) );
        setup();
        if( clonep() ) CHANNEL_D->register_relay_channel("chat");
}

int add_phrase(string who, string msg)
{
        msg = replace_string(msg, "?", "");
        msg = replace_string(msg, "？", "");
        msg = replace_string(msg, "？", "");
        msg = replace_string(msg, "!", "");
        msg = replace_string(msg, "！", "");
        msg = replace_string(msg, "啊", "");
        msg = replace_string(msg, "吗", "");
        msg = replace_string(msg, "耶", "");
        msg = replace_string(msg, "吧", "");

        if( msg!="" ) {
                add("memory/" + who, ({ msg }));
                return 1;
        } else return 0;
}

string make_reply()
{
}

void relay_channel(object ob, string channel, string msg)
{
        string who/*, phrase*/;

//        if( !userp(ob) || (channel != "chat") ) return;
        who=query("name", ob);

        // Don't process our own speech.
        if( ob==this_object() ) return;

        if( add_phrase(who, msg) && random(10) > 4 && strlen(msg)<500 )
                drool(msg,query("name", ob));
}

void relay_say(object ob, string msg)
{
        string who/*, phrase*/;

        if( !userp(ob) ) return;
        who=query("name", ob);

        // Don't process our own speech
        if( ob==this_object() ) return;

        if( add_phrase(who, msg) && random(10) > 4 && strlen(msg)<500 )
                drool(msg,query("name", ob));
}

void relay_emote(object ob, string verb)
{
        if( !userp(ob) ) return;

        switch(verb)
        {

        case "kick":
                if( random(10)<5 ) {
                        command("say 为什麽踢我？会痛耶！");
                        break;
                }
        case "hug":
        case "kiss":
        case "mo":
        case "18mo":
        case "nocloth":
        if( query("gender", ob) == "男性" || 
             query("gender", ob) == "无性" )
        {
                command("chat这算啥，"+query("name", ob)+"！我就喜欢这个调调儿！\n");
                command("chat 谁想得到这" + RANK_D->query_rude(ob)+"，竟然有龙阳之好。\n");
        }
        else
        {
                command("giggle");
                command("chat想不到"+query("name", ob)+"自动把豆腐送上来了。再开心没有了！");
        }
                message_vision("$N摇了摇头，对$n幽幽叹道：唉，你这又是何苦呢?\n",this_object(), this_player());
        default:
                if( random(10)<5 )
                        command(verb+""+query("id", ob));
                else
                        drool();
        }
}

varargs void drool(string msg, string who)
{
        mapping mem;
        string *ob;

        mem = query("memory");
        if( !mapp(mem) ) return;

        if( !msg || !who) {
                ob = keys(mem);
                who = ob[random(sizeof(ob))];
                msg = mem[who][random(sizeof(mem[who]))];
        }

        if( (strsrch(msg, "为什麽") >= 0) ) {
                if( sscanf(msg, "%*s为什麽%s", msg)==2 ) msg = "为什麽" + msg;
                switch(random(8)) {
                case 0: command("say " + who + "，你是在问我吗？"); break;
                case 1: command("say 关於" + msg + " ... "); break;
                case 2: command("say 呃 ... "); drool(); break;
                case 3: command("say 这个问题嘛 ...."); break;
                case 4: command("say " + who + "，知道这个问题的答案对你那麽重要么？"); break;
                case 5: command("say " + msg + "？"); break;
                case 6: command("say " + who + "你能不能说清楚一点？"); break;
                case 7: command("say " + who + "，我不懂你问的问题"); break;
                }
        }
        else if( (strsrch(msg, "你") >= 0)
        ||      (strsrch(msg, "□") >= 0)
        ||      (strsrch(msg, "drooler") >= 0)
        ||      (strsrch(msg, "Drooler") >= 0)) {
                if( sscanf(msg, "%*s你%s", msg) == 2 ) msg = "你" + msg;
                msg = replace_string(msg, "你", "我");
                msg = replace_string(msg, "□", "我");
                switch(random(10)) {
                case 0: command("say " + who + "，你是说" + msg + "吗？");break;
                case 1: command("say 你确定" + msg + "？");     break;
                case 2: command("say " + msg + "跟你有什麽关系？");     break;
                case 3: command("say 嗯 ... " + who + "说得好"); break;
                case 4: command("say " + who + "你为什麽对" + msg + "这麽有兴趣？"); break;
                case 5: command("say 为什麽你认为" + msg + "？"); break;
                case 6: command("say 换个话题吧"); drool(); break;
                case 7: command("say 才怪"); break;
                case 8: command("say 不一定吧？"); break;
                case 9: command("say 有这个可能 ...."); break;
                }
        }
        else if( (strsrch(msg, "我") >= 0)) {
                if( sscanf(msg, "%*s我%s", msg) == 2 ) msg = "我" + msg;
                msg = replace_string(msg, "我", "你");
                msg = replace_string(msg, "?", "");
                switch(random(8)) {
                case 0: command("say 你是说" + msg + "吗？"); break;
                case 1: command("say 真的？" + msg + "？");     break;
                case 2: command("say 如果" + msg + "，我能帮你什麽忙吗？");break
;
                case 3: command("hmm"); break;
                case 4: command("say 你认为" + msg + "？"); break;
                case 5: command("say 我有同感"); break;
                case 6: command("say 你说的「" + msg + "」我不能苟同"); break;
                case 7: command("say 有关「" + msg + "」的话题到此为止好吗？");;
                }
        } else {
                switch(random(20)) {
                        case 0: command("say 为什麽说" + msg + "?"); break;
                        case 1: command("say 「" + msg + "」是什麽意思？"); break;
                        case 2: command("say " + msg + "？"); break;
                        case 3: command("grin"); break;
                        case 4: command("smile"); break;
                        case 5: command("?"); break;
                        case 6: command("say ...."); break;
                        case 7: command("hmm"); break;
                        case 8: command("say " + rnd_say[random(sizeof(rnd_say))]); break;
                        case 9: command("say 你怎麽知道" + msg + "?"); break;
                        case 10: command("say 刚刚" + who + "不是说了，" + msg);
                        case 11: command("say 我当然知道，" + msg); break;
                        case 12: command("say 然後呢？"); break;
                        case 13: command("say 真的吗？"); break;
                        case 14: command("say 我不这麽认为。"); break;
                        default:
                                break;
                }
        }
}

void reset()
{
        delete("memory");
}

int accept_object()
{
        return 1;
}
void init()
{
    object ob;

    ::init();
    if( interactive(ob = this_player()) && !is_fighting() ) {
         remove_call_out("greeting");
         call_out("greeting", 1, ob);
    }
    add_action("do_dajia","hit");
    add_action("do_dajia","fight");
}

void greeting(object ob)
{
    if( !ob || environment(ob) != environment() ) return;
    say( "桃谷六仙争先恐后地招呼：过来和我们六兄弟喝酒！\n");
    message_vision("桃干仙，斜了$N一眼，突然大喊起来：“快拿酒来！”\n", ob);
    message_vision("桃枝仙拍着桌子，喊道：“老子今天要一边喝酒，一边看着人
把$N分成九块！\n", ob);
    message_vision("桃叶仙跳了过来，一把抓住$N，嚷道：我第一！我第一！\n", ob);
    say("桃花仙横着短棍进来，一屁股坐下，提酒就喝。\n");
    message_vision("桃实仙冲着$N挤挤橘皮老脸，一串串酒嗝冲着$N直冒。\n", ob);
}

int do_dajia()
{
    object ob;

    ob = this_player();
    message_vision("桃谷六仙一拥而上，提起老拳将$N一顿臭打！\n",ob);
    message_vision("$N躺在地上，大叫＂桃谷六爷爷，六位大英雄饶命！＂桃谷六仙六张\n",ob);
    message_vision("皮老脸顿时都露出笑容：＂$N有眼光，是个大好人，收手了不打了！\n",ob);
    set("qi", 10, ob);
    return 1;
}
int do_kill()
{
    object ob;
    ob = this_player();
    message_vision("桃谷六仙一拥而上，提起老拳将$N往死里打！桃根仙和桃干仙，桃枝\n",ob);
    message_vision("仙，桃叶仙分抓$N四肢，只听得一声惨呼，满地鲜血内脏，桃谷四仙\n",ob);
    message_vision("竟把$N活生生撕成四片，桃花仙和桃实仙守在旁边，别人都救护不了！\n",ob);
    ob->die();
    return 1;
}