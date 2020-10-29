#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;
#define THROWTIME 30    //基础禁闭分钟
int is_chat_room() { return 1; }
int do_check(string arg); 
int do_tongji(string arg);
int throwing(object me, int i, string bmsg);
void create()
{
        set("short", NOR HIW "监测室" NOR);
        set("long", @LONG
这是没有建造工作室的巫师的临时住处，这里的设备非常简单，只有
一些常用物品。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                "down" : __DIR__"workroom",
        ]));

          set("objects", ([ 
//          "/u/mud/charm.c":1,
//      "/kungfu/class/misc/haigui":1,
          ]));
        set("valid_startroom", 1);
        //set("no_fight", "1");
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "up" && ! wizardp(me))
                return notify_fail("那里只有巫师才能进去。\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_check","cc");
                add_action("do_tongji","tj");
}
int do_check(string arg)
{
        object obj;
                string msg;
                string msg1,msg2,msg3,msg4,msg5;
                
        object me = this_player();
        if(! arg || arg == "")
            return notify_fail("请输入要还阳者的id？\n");
        obj = find_player(arg);
        if(!obj)
            return notify_fail("没有这个人。\n");
        
                msg1 = BUFF_D->check_buff(obj, "lbwb-shen")+"/"+ BUFF_D->get_buff_overtime(obj, "lbwb-shen");   
        msg2 = BUFF_D->check_buff(obj, "powerup")+"/"+ BUFF_D->get_buff_overtime(obj, "powerup");
        msg3 = BUFF_D->check_buff(obj, "powerofsun")+"/"+ BUFF_D->get_buff_overtime(obj, "powerofsun");
        msg4 = BUFF_D->check_buff(obj, "powerofmoon")+"/"+ BUFF_D->get_buff_overtime(obj, "powerofmoon");
        msg5 = BUFF_D->check_buff(obj, "powerofstar")+"/"+ BUFF_D->get_buff_overtime(obj, "powerofstar");
                
        msg = arg+"的状态如下:\n";              
        msg+= "凌波微步:"+msg1+"\n";
                msg+= "powerup:"+msg2+"\n";
                msg+= "太阳之力:"+msg3+"\n";
                msg+= "月亮之力:"+msg4+"\n";
                msg+= "星辰之力:"+msg5+"\n";            
                tell_object(me,msg);
      return 1;
}
int do_tongji(string arg)
{
        object player;
        string msg,skname,sk;
                int sklv,sklvmax,sklvmax2;            
        object me = this_player();
                
        if(! arg || arg == "")
            return notify_fail("请输入玩家ID！\n");
                        
        player = find_player(arg);
                
        if(!player)
            return notify_fail("没有这个人。\n");

        sk = "force";
        skname = to_chinese(sk);
        sklv = player->query_skillo(sk,1);
        sklvmax = to_int(pow(to_float(pow(to_float(query("level", player))+1.0, 3.0)*10000/100), 1.0 / 3)*10) + 1;
        sklvmax2 = to_int(pow(to_float(query("combat_exp", player)/100), 1.0 / 3)*10) + 1;
        if (sklv < 2000) return 0;
        if (sklv < sklvmax * 13 / 10) return 0;
        if (sklv < sklvmax2 * 13 / 10) return 0;
         //write(HIY + "统计到"+player->name()+"("+query("id", player)+")的"+skname+"("+sk+")的等级"+(string)sklv+"异常\n" + NOR);
        log_file( "static/throw_skup", player->name()+"("+query("id", player)+")的"+skname+"("+sk+")的等级"+(string)sklv+"异常\n");
        throwing(player, THROWTIME, skname+"("+sk+")等级异常达到" + (string)sklv + "级");
        tell_object(player, NOR BLINK HIR "\n如果有异议，msg mail redl，留下你的解释。\n确定冤情后对于被禁闭的时段，可获补偿50NT/小时。\n\n" NOR);
        return 1; 

}
int throwing(object me, int i, string bmsg)
{
        int c, p = query("redlworkroom/prison/num", me);
        
        if (undefinedp(p) || !p) p = 0;
        
        c = (60 * i) * (5 + p) / 5;
        set("redlworkroom/prison/bmsg", bmsg, me);
        set("redlworkroom/prison/ti", i, me);
        set("redlworkroom/prison/time", query("online_time", me) + c , me);
        set("redlworkroom/prison/num", p + 1, me);
        
        message_vision(append_color(NOR + YEL + "虚空中穿过来一只大如山岳的巨掌，对着$N" + NOR + YEL + "拦腰一捞，再缩回去就此不见了。\n" + NOR, YEL), me);
        me->move("/u/redl/prison");
        return 1;
}

int auto_check()
{

        object player;
        string msg,skname,sk;
                int sklv,sklvmax,sklvmax2;            
        object me = this_player();
                
        object *users;

        int rall;
                
                call_out("auto_check",15);
        users = users();
        rall = sizeof(users);
        player = users[random(sizeof(users))];
                
        sk = "force";
        skname = to_chinese(sk);
        sklv = player->query_skillo(sk,1);
        sklvmax = to_int(pow(to_float(pow(to_float(query("level", player))+1.0, 3.0)*10000/100), 1.0 / 3)*10) + 1;
        sklvmax2 = to_int(pow(to_float(query("combat_exp", player)/100), 1.0 / 3)*10) + 1;
        if (sklv < 2000) return 0;
        if (sklv < sklvmax * 13 / 10) return 0;
        if (sklv < sklvmax2 * 13 / 10) return 0;
         //write(HIY + "统计到"+player->name()+"("+query("id", player)+")的"+skname+"("+sk+")的等级"+(string)sklv+"异常\n" + NOR);
        log_file( "static/throw_skup", player->name()+"("+query("id", player)+")的"+skname+"("+sk+")的等级"+(string)sklv+"异常\n");
        throwing(player, THROWTIME, skname+"("+sk+")等级异常达到" + (string)sklv + "级");
        tell_object(player, NOR BLINK HIR "\n如果有异议，msg mail redl，留下你的解释。\n确定冤情后对于被禁闭的时段，可获补偿50NT/小时。\n\n" NOR);
        return 1; 

}
