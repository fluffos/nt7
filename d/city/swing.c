// * TLBB MUDLIB
//* $Header: /home/mud/cvsroot/tlbbmud/tlbb/tlbb_mudlib/t/ly/swing.c,v 1.4 2000/04/15 05:30:46 mud Exp $
// redl 2013/9

#include <ansi.h>
#include <room.h>
#include <transmsg.h> 
inherit ROOM;

string look_swing(object me);
string *high_msg = ({
        "吓得尖声呼叫“啊～～～”\n",
        "脸色苍白，紧张得连声都不敢出了。\n",
        "只觉得头晕眼花，生怕摔下来。\n",
        "盼着赶紧停下来。\n",
        "大声叫着“真好玩啊！”\n",
        "颤声喊道“我怕怕～～～～”\n",
});
string *mid_msg = ({
        "大叫“爽啊！真刺激！”\n",
        "兴奋得满脸通红，但就是不敢睁眼。\n",
        "似乎还觉得不过瘾，还想再高一些。\n",
        "一付很轻松的样子。\n",
        "紧张的汗都出来了。\n",
        "哈哈大笑，从没这么高兴过。\n",
});
string *low_msg = ({
        "高兴的叫个不停。\n",
        "兴奋得在秋千上手舞足蹈，也不怕摔下来。\n",
        "觉得有点头晕，不过还可以坚持。\n",
        "不由想起了童年时光。\n",
        "感觉轻松自如，还想再高一点。\n",
        "从秋千上站了起来，以显示高超的技术。\n",
});

int clean_up() { return 1;}

int do_clean()
 {
        remove_call_out("do_clean");
        set("enter_num", 0);    
        delete_temp("enter_num");
        call_out("do_clean", 3600 + random(1800));
        return 1; 
}

int do_gun(object me, int i)
{
                message_vision(NOR + "秋千突然无风自动，荡起来打在$N头上，将$N打到北方去了。\n" + NOR, me);
                me->move("/d/city/kedian4");
                me->start_busy(i);
                message_vision(NOR + "$N屁滚尿流地从南方滚了过来。\n" + NOR, me);
                me->command("stat");
                tell_object(me, "你一屁股跌坐到地上，半天都爬不起来。\n");
                return 1;
}

void create()
{
        set("short", "秋千园");
        set("long", 
        "一个废弃的花园，杂草丛生，落叶缤纷。左边有一个小石桌，\n"
        "几尊石凳。右边有两棵大树，树中间挂着一架"+CYN"秋千"NOR+"。一阵风吹过，\n"
        "枯叶在空中飞舞，那曾经热闹过的秋千也轻轻荡了起来，仿佛诉\n"
        "说着往日的记忆。\n"
        );
        set("exits", ([ /* sizeof() == 2 */
            "north" : __DIR__"kedian4",
                        "northeast" :  "/d/city/qiyuan/xxzl1",
                        "northwest" : "/u/redl/school/gate",  
]));
        set("item_desc", ([
                "秋千": (: look_swing :),
                "swing": (: look_swing :),
        ]) );
//            set("outdoors", 1);
                set("no_fight", 1);
                set("no_magic", 1);
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_smoke", 1);
                set("no_sleep_room", 1);
                        set("enter_num", 0);

        set("objects", ([ 
                                                "/u/redl/obj/luckytree" : 1,
                                                     "/adm/npc/btc" : 1,  
        ])); 

        setup();
        call_out("do_clean", 3600 + random(1800));
                "/clone/board/swing_b"->foo(); 
        
}

string look_swing(object me)
{
        return "这是一架用藤条编就的秋千(swing)，虽然已久无人用，\n但看起来还结实，可以坐上去(sit)试试，\n也可以抱你心爱的人坐上去(lift)。\n";
}

int do_action(string arg)
{
                int i, time, flag = 0;
        string action = query_verb();
        object me = this_player();
        
        time = query_temp("cityswing/action_t", me);
        if ((!time) || ( time && (time()-time > 1) )) {
                set_temp("cityswing/action_t", time(), me);
                set_temp("cityswing/action_n", 0, me);
        }
        addn_temp("cityswing/action_n", 1, me);
        i = query_temp("cityswing/action_n", me);
        
        if (action=="equip" || 
                        arg=="all") 
                flag = 1;
                
        if (action=="news" || action=="member" || action=="ntstore" || action=="combat" || action=="help" || action=="maphere") flag = 0;
        
        if (flag || 
                i > 6) {
                        do_gun(me, 90);
                        return -1;
                }
        return 0;
}

int is_owner(object me)
{
        if (query("id", me) == "redl" ||
                query("id", me) == "gigi" ||
                query("couple/couple_id", me) == "redl" ||
                wiz_level(me) > 6) return 1;
        return 0;
}

int do_push2(string arg)
{
        int i;
        object me,ob;
        me = this_player();
        if(!arg || !objectp(ob = present(arg, environment(me))))
                return notify_fail("你要推谁啊？\n");
        if( arg == query("id", me))return notify_fail("你没法自己推自己啊。pig...:P\n");
        if( is_owner(ob) ) return notify_fail("你这样做不太好吧？...:P\n");
        if( query_temp("marks/swingm", ob)){
                message_vision("$N又使劲推了$n一下，秋千荡的飞了起来。\n",me,ob);
                message_vision(RED"$N脚下一个不稳，从秋千上跌了下来，摔了个大屁堆儿！\n"NOR,ob);
                remove_call_out("swing_left");
                remove_call_out("swing_right");
                delete_temp("marks/sitted", ob);
                delete_temp("marks/swingm", ob);
                delete("marks/sitted", this_object());
                ob->start_busy(10);
                return 1;
        } else {
                do_gun(ob, 900);
                return 1;
        }
        return 1;
}

void init()
{
        object me = this_player();
        string id = query("id", me);
        add_action("do_sit", "sit");
                add_action("do_lift", "lift");
        add_action("do_dang", "dang");
        add_action("do_push", "push");
        add_action("do_down", "down");
        if ( !is_owner(me) ) add_action("do_action", "");
        if ( is_owner(me) ) add_action("do_push2", "push2");
}

int do_sit(string arg)
{
                int rnd = 0;
        string sitter, id;
        object me,ob;
        me = this_player();
        id = query("id", me);
        if(me->is_fighting()) return notify_fail("一边打架一边荡秋千？你没事吧？\n");
        if(me->is_busy()) return notify_fail("你正忙着，没空荡秋千。\n");
        if(!arg) {
                //write("你想自己即不是红莲也不是芝芝，还是(sit swing)再玩吧。\n");
                if (!is_owner(me)) {
                        if ( query("enter_num") > 25 ) {//可能有人试图想刷
                                                                do_gun(me, 60);
                                return 1;
                        }
                        if ( query("enter_num") > 9 || 
                                (query("online_time", me) < 43200) || 
                                ( (query("enter_id/"+id)) && (time() - query("enter_id/"+id) < 43200) ) || 
                                wiz_level(me) >= wiz_level("(wizard)") ) {
                                if ( (query_temp("enter_num/"+id)) && (query_temp("enter_num/"+id) > 2) ) {//可能有人试图想刷
                                        do_gun(me, 300);
                                        return 1;
                                }
                                addn_temp("enter_num/"+id, 1);
                                message_vision("$N坐在了地上。\n",me);
                                me->start_busy(3);
                                return 1;
                        }
                        //rnd = random(2);
                        set("enter_id/"+id, time());
                                                addn("enter_num", 1);
                }
                message_vision("$N坐在了地上。\n",me);
                //if (!rnd) {
                                        set_temp("can_enterredlroom", 1, me);
                                        message_vision(YEL + "$N在" + MAG + "相思树" + YEL + "下迷迷糊糊地睡着了...\n" + NOR, me);
                                        me->move("/u/redl/private_room/dating");
                                        message_vision(YEL + "大片紫青色烟雾聚拢弥散过后，$N来到了神秘的化乐天遗迹。\n" + NOR, me);
                    //return 1;
                //}
                //me->start_busy(3);
                return 1;
        }
        if(arg != "swing") return notify_fail("你要坐什么？\n");
        if(query("marks/sitted")) {
                sitter=query("marks/sitted", this_object());
                ob = present(sitter,environment(me));
                if( (ob) && (query_temp("marks/sitted", ob))){
                        write("秋千上已经有人了。\n");
                        return 1;
                }
        }
        message_vision("$N坐到了秋千上面。\n", me);
        write("你可以自己荡秋千(dang)，也可以让别人推一把(push)。\n");
        set("marks/sitted",query("id", me));
        set_temp("marks/sitted", 1, me);
        return 1;
}

int do_lift()
{
        string sitter;
        object me,ob;
        me = this_player();
        if(query("marks/sitted")) {
                sitter=query("marks/sitted", this_object());
                ob = present(sitter,environment(me));
                if( (ob) && (query_temp("marks/sitted", ob))){
                        write("秋千上已经有人了。\n");
                        return 1;
                }
        }
        sitter = query("couple/couple_id", me );
        if (!sitter) {
                 write("你还没有爱人。\n");
                 return 1;
        }
        ob = present(sitter, environment(me));
        if (!objectp(ob)) {
                 write("你想抱谁上秋千？\n");
                 return 1;
        }
        if( !ob->is_character() || query("not_living", ob) ) {
                 write("看清楚了，那不是活人！\n");
                 return 1;
        }
        message_vision("$N轻轻抱起$n放到了秋千上面。\n", me,ob);
        tell_object(ob, "你可以自己荡秋千(dang)，也可以让别人推一把(push)。\n");
        set("marks/sitted",query("id", ob));
        set_temp("marks/sitted", 1, ob);
        return 1;
}

int do_dang()
{
        int i;
        object me;
        me = this_player();
        if(me->is_fighting()) return notify_fail("一边打架一边荡秋千？你没事吧？\n");
        if(me->is_busy()) return notify_fail("你正忙着，没空荡秋千。\n");
        i=query_temp("marks/swingm", me);
        if( !query_temp("marks/sitted", me) )
        return notify_fail("你还没坐到秋千上。\n");
        if( !query_temp("marks/swingm", me)){
                message_vision("$N脚下一使劲，秋千缓缓的荡了起来。\n",me);
                set_temp("marks/swingm", 3, me);
                call_out("swing_left",7,me);
                return 1;
        }
        if( query_temp("marks/swingm", me)>9){
                message_vision("$N脚下再一使劲，秋千荡的飞了起来。\n",me);
                message_vision(RED"$N脚下一个不稳，从秋千上跌了下来，摔了个大屁堆儿！\n"NOR,me);
                remove_call_out("swing_left");
                remove_call_out("swing_right");
                delete_temp("marks/sitted", me);
                delete_temp("marks/swingm", me);
                delete("marks/sitted", this_object());
                return 1;
        }
        
        message_vision(YEL"$N使劲荡了一下，秋千荡的更高更快了！\n"NOR,me);
        i = i + 3;
        set_temp("marks/swingm", i, me);
        remove_call_out("swing_left");
        remove_call_out("swing_right");
        call_out("swing_left",10-i,me);
        return 1;
}

int do_push(string arg)
{
        int i;
        object me,ob;
        me = this_player();
        if(me->is_fighting()) return notify_fail("一边打架一边荡秋千？你没事吧？\n");
        if(me->is_busy()) return notify_fail("你先把手头的事忙完再说吧。\n");
        if(!arg || !objectp(ob = present(arg, environment(me))))
                return notify_fail("你要推谁啊？\n");
        if( arg == query("id", me))return notify_fail("你没法自己推自己啊。pig...:P\n");
        if( !query_temp("marks/sitted", ob) )
                return notify_fail("对方不在秋千上，你没法推。\n");
        if(ob->is_fighting()) return notify_fail("一边打架一边荡秋千？你没事吧？\n");
        if(ob->is_busy()) return notify_fail("对方正忙着呢。\n");
        i=query_temp("marks/swingm", ob);
        if( !query_temp("marks/swingm", ob)){
                message_vision(YEL"$N轻轻推了$n一下，秋千缓缓荡了起来。\n"NOR,me,ob);
                set_temp("marks/swingm", 3, ob);
                call_out("swing_left",7,ob);
                return 1;
        }
        if( query_temp("marks/swingm", ob)>9){
                message_vision("$N又使劲推了$n一下，秋千荡的飞了起来。\n",me,ob);
                message_vision(RED"$N脚下一个不稳，从秋千上跌了下来，摔了个大屁堆儿！\n"NOR,ob);
                remove_call_out("swing_left");
                remove_call_out("swing_right");
                delete_temp("marks/sitted", ob);
                delete_temp("marks/swingm", ob);
                delete("marks/sitted", this_object());
ob->set_short_desc(0); 

                return 1;
        }
        
        message_vision(YEL"$N又轻轻推了$n一下，秋千荡的更高更快了！\n"NOR,me,ob);
        i = i + 3;
        set_temp("marks/swingm", i, ob);
        remove_call_out("swing_left");
        remove_call_out("swing_right");
        call_out("swing_left",10-i,ob);
        return 1;
}
int do_down()
{
        object me;
        me = this_player();
        if( !query_temp("marks/sitted", me) )
        return notify_fail("这个方向没有出路。\n");
        message_vision("$N从摇荡的秋千上蹦了下来。\n",me);
        remove_call_out("swing_left");
        remove_call_out("swing_right");
        delete_temp("marks/sitted", me);
        delete_temp("marks/swingm", me);
        delete("marks/sitted", this_object());
me->set_short_desc(0); 

        return 1;
}

void swing_left(object me)
{
        int i;
        string msg;
        i=query_temp("marks/swingm", me);
        if(i>0) {
                if(i>3) {
                        if(i>6) {
                                msg = "秋千向前荡的又高又直，$N"+high_msg[random( sizeof( high_msg ))];
                                message_vision(msg,me);
                                call_out("swing_right",10-i,me);
                                return;
                        }
                        msg = "秋千飞一样向前荡去，$N"+mid_msg[random( sizeof( mid_msg ))];
                        message_vision(msg,me);
                        call_out("swing_right",10-i,me);
                        return;
                }
                msg = "秋千缓缓向前荡去，$N"+low_msg[random( sizeof( low_msg ))];
                message_vision(msg,me);
                call_out("swing_right",10-i,me);
                return;
        }
}

void swing_right(object me)
{
        int i;
        string msg;
        i=query_temp("marks/swingm", me);
        i = i-1;
        if(i<1) {
                message_vision("秋千缓缓停了下来，$N意犹未尽的走下秋千。\n",me);
                delete_temp("marks/sitted", me);
                delete_temp("marks/swingm", me);
                delete("marks/sitted", this_object());
                return;
        }
        set_temp("marks/swingm", i, me);
        if(i>0) {
                if(i>3) {
                        if(i>6) {
                                msg = "秋千向后荡的又快又猛，$N"+high_msg[random( sizeof( high_msg ))];
                                message_vision(msg,me);
                                call_out("swing_left",10-i,me);
                                return;
                        }
                        msg = "秋千高高的向后荡去，$N"+mid_msg[random( sizeof( mid_msg ))];
                        message_vision(msg,me);
                        call_out("swing_left",10-i,me);
                        return;
                }
                msg = "秋千缓缓向后荡去，$N"+low_msg[random( sizeof( low_msg ))];
                message_vision(msg,me);
                call_out("swing_left",10-i,me);
                return;
        }
}

int valid_leave(object me, string dir)
{
        if( query_temp("marks/sitted", me) )
        return notify_fail("你先要从秋千上下来(down)才能离开。\n");
        return ::valid_leave(me, dir);
        return 1;
}


