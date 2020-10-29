// 这是为新任务所做的房子
// add by chhu
// Modified by haiyan

inherit ROOM;
#include <ansi.h> 
#include <room.h> 

void create()
{
     set("short", "峭壁");
        set("long", @LONG
这是位于终南山的一处峭壁，远处传来汹涌的流水声，周围是阴
暗的丛林。一面光滑的大石(stone)上面似乎密密麻麻地刻着些字。
LONG );
     set("exits", ([ /* sizeof() == 1 */ 
         "south" : "/d/changan/zhongnan.c",
     ])); 

     set("objects", ([ 
         "/d/wudang/quest/tianshi" : 1,
     ]));

     set("coor/x", -320);
        set("coor/y", 10);
        set("coor/z", 0);
        setup(); 
}

void init() 
{ 
    add_action("do_look","look"); 
} 

int do_look(string arg) 
{ 
    string msg; 
    if (!arg || arg != "stone")  return 0; 
    msg  = HIC "----------------------------------------------------------\n"NOR; 
    msg += WHT BBLU "                        捉鬼任务简介                      \n"NOR; 
    msg += HIC "----------------------------------------------------------\n"NOR; 
    msg += "    武当派和全真教弟子身为道士，自然会降妖驱魔的本事。可以\n";
    msg += "向李天师打听任务。降妖驱魔需要两件宝物，一是"HIY"符纸"NOR"，二是"HIM"桃木\n";
    msg += "剑"NOR"。领取任务时，李天师会给你"HIY"符纸"NOR"，而"HIM"桃木剑"NOR"则需要自己想办法\n";
    msg += "了。:)\n";
    msg += "    这项工作有一定的难度，妖魔一般都是隐身看不见的，你只能\n";
    msg += "够感觉它的存在，并利用"HIY"符纸"NOR"使其现身。当你感觉到妖魔存在时，\n";
    msg += "只可使用"HIC"shoufu"NOR"指令，不能kill它。但妖魔一般都比较厉害，你最\n";
    msg += "好做足充分的准备。完成任务后，将"HIY"符纸"NOR"交还给李天师，即可得到\n";
    msg += "奖励。\n";
    this_player()->start_more(msg); 
    return 1; 
} 
