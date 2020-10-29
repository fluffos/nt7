// /d/city/npc/wenyi

#include <ansi.h>
inherit NPC;

int ask_xia1();
string ask_gift();
#define this_quest_is_open "yes"
 
void create()
{
        object ob;
        object sb;
        set_name("温仪", ({ "wen yi", "wen" }));
        set("long", 
        "她就是金蛇郎君的妻子温仪。\n"
        "一位三十来岁的女子，容貌清秀，有着一种成熟的韵味。\n");
        set("gender", "女性");
        set("age", 36);
        set("attitude", "friendly");
        set("shen", 1000);
        set("str", 35);
        set("int", 30);
        set("con", 25);
        set("dex", 27);
        
         set("max_qi", 999999);
         set("max_jing", 999999);
         set("max_neili", 999999);
         set("neili", 999999);
        set("jiali", 10);
        set("combat_exp", 5000);
         

    set_skill("force", 10);
    set_skill("yijin-jing", 10);
    set_skill("dodge", 10);

    set_skill("shaolin-shenfa", 10);
    set_skill("cuff", 10);
    set_skill("wenjia-daofa", 10);
    set_skill("parry", 10);
    set_skill("blade", 10);
    set_skill("wenjia-quan", 10);
    set_skill("literate", 10);

          map_skill("force", "hunyuan-yiqi");
    map_skill("dodge", "shaolin-shnfa");
    map_skill("cuff", "wenjia-quan");
        map_skill("parry", "wenjia-daofa");
        map_skill("blade", "wenjia-daofa");
    prepare_skill("cuff", "wenjia-quan");
    
    set("inquiry", ([
                "温青青" : "青青是我女儿,她姓夏,叫夏青青.\n",
                "夏青青" : "青青是我女儿.\n",
                "温方山" : "温方山是我爹爹.\n",
                "金蛇郎君" : "名震天下的金蛇郎君就是我的夫君。\n",
                "温家五老" : "哼......\n",
                "夏雪宜" : (: ask_xia1 :),
                "宝物" : (: ask_gift :),
                "掌法秘籍" : (: ask_gift :),
                "金蛇掌法" : (: ask_gift :),
        ]));
 
        setup(); 
        
        if (clonep()) {
                ob = unew("/d/xiangyang/wen/quest/obj/jszf-book");
                if (!ob) ob = new("/clone/money/gold");
                ob->move(this_object());
                sb = unew("/d/xiangyang/wen/quest/obj/gift");
                if (!sb) sb = new("/clone/money/gold");
                sb->move(this_object()); 
                
          carry_object(ARMOR_D("flower_shoe"))->wear();
    carry_object(ARMOR_D("pink_cloth"))->wear();

        }
         
     
}

void init()
{
        add_action("do_comfort", "comfort");
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("温仪对$N淡淡一笑，又转过身去，眉宇间没有丝毫恐惧。”\n", ob);
        message_vision("$N心中忽然觉得：“自己怎麽这麽无耻，对一个手无寸铁的人也要下此毒手？”\n", ob);
}

int ask_xia1()
{
        object me = this_player();
        string msg;
        msg = CYN"温仪听到$N的询问,身子一震,脸色大变。\n"NOR;
        message_vision(msg, me);
                
    if( query_temp("quest/金蛇掌法/start",1, me)){
        remove_call_out("do_happen1");
        call_out("do_happen1",3,me);
                return 1;
        }
        msg = CYN"温仪脸色变了几变,渐渐平静下来,对$N说:你问他作什么?\n"NOR;
        message_vision(msg,me);
        set_temp("quest/jinshe2/fail", 1, me);
        return 1;
}

int do_happen1(object me)
{
        string msg;
        //if (base_name(environment(me)) != HERE)               return 1;
        msg = CYN"温仪叹了口气,道:既然你是青青的朋友,我就告诉你吧。\n"NOR;
        msg+= CYN"温仪顿了顿道:那是一段陈年旧事,十八年前我遇到了青青的父亲夏雪宜,也就是金蛇郎君。\n"NOR;
        msg+= CYN"温仪道:我们相亲相爱,本以为,本以为真的可以化解父辈的仇恨,可是爹爹......。\n"NOR;
        msg+= CYN"温仪突然眼圈发红,哽咽着说不出话来......\n"NOR;
        msg+= HIG"温仪哭得梨花带雨,楚楚可怜,你忍不住想"HIC"安慰(comfort)"HIG"她一下.\n"NOR;
        message_vision(msg, me);
         set("quest/jinshe2/step1", 1, me);
        return 1;       
    }
int do_comfort(string arg)
{
       string msg;
       object me=this_player();
       if( !query("quest/jinshe2/step1", this_player()))return 0;
        
        if( !arg ) return notify_fail("你说什么？\n");
        
        message_vision("$N轻声安慰道：" + arg + "\n", this_player());
        if( strsrch(arg, "夏夫人") >=0 && (strsrch(arg, "你别难过") >=0
         || strsrch(arg, "是金蛇郎君") >=0 || strsrch(arg, "特意叫我来找你的") >=0 )) {
                command("ah");
                command("say 你说的都是真的?!!!\n");
                command("touch"+query("id", this_player()));
                set_temp("quest/jinshe2/step2", 1, this_player());
                delete_temp("quest/jinshe2/step1",1, this_player());
                return 0;
        } else {
                command("say 他这个负心人,丢下我们娘儿俩,一走就是十八年.");
                msg = HIC"安慰人总得有个称呼,说法,消息和理由吧？\n"NOR;
                message_vision(msg, me);
        }
        
        }

int accept_object(object who, object ob)
{
    string msg;
    object me = this_player();
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return notify_fail("你没有这件东西。\n");
        if( !query_temp("quest/jinshe2/step2", this_player()) && !query("quest/jinshe2/xin", this_player()))return 0;
        if (userp(ob)) {
               command("?"+query("id", who));
               command("say 你把人打晕想干什么？");
               this_object()->kill_ob(who);
               return notify_fail("糟糕，穿帮了！\n");
        }
        if( query("id", ob) == "xinjian" && query("name", ob) == "家信"){
                if( query("quest/jinshe2/xin", this_player())){
                        command("wuwu");
                        command("say 这...这是雪宜的字体。");
                        command("touch"+query("id", who));
                        command("say 雪宜从前留下了一批宝物,送你当作感谢吧!"); 
                        set("quest/jinshe2/pass", 1, this_player());
                        call_out("destroying", 1, ob);
                        return 1; 
            }
            command("hmm");
            command("say 你是从哪里得到的这封信?当心我去找月影举报你!");
            msg = HIG"温仪柳眉一皱:来人啊,把这个骗子轰出去!!!。\n"NOR;
            message_vision(msg, me);
            message_vision(HIR"\n一群家丁应声而出,将$N乱棒打晕,丢了出去。\n"NOR,me);
            me->unconcious();
            me->move("/d/city/chmiao");
            tell_room(environment(me),HIR"突然涌出一群温府家丁,将" + me->name(1) +"乱棍打晕,丢了出去"NOR);
            return 1;
          }
        if( query("name", ob) != HIY"金蛇锥"NOR || query("id", ob) != "jinshezhui"){
               command("shake"+query("id", who));
               command("say 谢谢你啦。");
               return 0;
        }
        if( !query_temp("quest/金蛇剑法/金蛇锥", this_player()) )
        {
             command("hmm");
              command("say 你是从哪里得到的?当心我去找月影和戴黛举报你!");
             msg = HIG"温仪柳眉一皱:来人啊,把这个骗子轰出去!!!。\n"NOR;
             message_vision(msg, me);
             message_vision(HIR"\n一群家丁应声而出,将$N乱棒打晕,丢了出去。\n"NOR,me);
             me->unconcious();
             me->move("/d/city/chmiao");
             tell_room(environment(me),HIR"突然涌出一群温府家丁,将" + me->name(1) +"乱棍打晕,丢了出去"NOR);
         call_out("destroying", 1, ob);
             return 1;
}
        command("ah"+query("id", who));
        command("say 这是雪宜的随身之物,看来你是他托付的人,如果有他的"HIY"消息"CYN"的话,麻烦请您告诉我一声.\n"NOR);
        command("thank"+query("id", who));
        msg = HIG"温仪向你打听有关夏雪宜的"HIW"消息"HIG",去看看夏雪宜的"HIR"遗物"HIG"里有什么线索吧。\n"NOR;
        message_vision(msg, me);
        set("quest/jinshe2/xin", 1, who);
        set_temp("open", 0, who);
        delete_temp("quest/jinshe2/step2",1, who);
        call_out("destroying", 1, ob);
        return 1;
}
void destroying(object ob)
{
        if (!ob) return;
        if (userp(ob)) command("drop "+ob->parse_command_id_list()[0]);
        else destruct(ob);
}

string ask_gift()
{
        object ob, sb,me = this_player();
        mapping quest;
  
  if( !query("quest/jinshe2/pass", me) && !query("quest/jinshe2/gift", me) )
        return "耶?你怎么突然说这么奇怪的事情?\n";
        
        if ( is_busy() || is_fighting())
                return "你没看到我正忙着么？\n";
  
        sb = present("box", this_object());
        ob = present("zhangfa miji", this_object());
        if ( !ob && !sb)
                return "耶？东西给我放到那里去了？\n";

/*time=time()-query("quest/jinshe2/zf_time", me);
        if( query("quest/jinshe2/zf_time", me) && time<86400 && !wizardp(me) && !query("env/debug", me) )
                return "你不是已经问过了?真是贪得无厌!!!\n";
*/
        quest=query("quest/jinshe2", me);

        if ( quest["pass"] ) {
                if ( ob ) {
                        set("owner", me, ob);
                        ob->move(me);
                        set("quest/jinshe2/zf_time", time(), me);
                        return "好吧，这本「掌法图解」你拿回去好好研究研究。\n";
                }
                else
                        return "你要的「掌法图解」已经给别人拿走了\n";
        }
        if ( quest["gift"] ) {
                if ( sb ) {
                        set("owner", me, sb);
                        sb->move(me);
                        set("quest/jinshe2/zf_time", time(), me);
                        return "谢谢你,家夫留下的这个「包裹」就送给你吧.\n";
                }
                else
                        return "真不巧,我这里现在没有,你过阵子再来吧.\n";
        }

        if( query("registered", me)<3 )
                return "我现在很忙，没兴趣和你多罗嗦！\n";

}