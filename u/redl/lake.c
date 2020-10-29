// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 


string look_bi(object me)
{
        me->remove_call_out("do_open");
        call_out("do_open", 6, me); 
        return "\n"
HIK 
"我一直想要 和你一起 走上那条美丽的山路\n"
"有柔风 有白云 有你在我身旁\n"
"倾听我快乐和感激的心\n"
"我的要求其实很微小 只要有过那样的一个夏日\n"
"只要走过 那样的一次\n"
"而朝我迎来的 日复以夜 却都是一些不被料到的安排\n"
"还有那麽多琐碎的错误 将我们慢慢地慢慢地隔开\n"
"让今夜的我 终於明白\n"
"所有的悲欢都已成灰烬 任世间哪一条路我都不能\n"
"与你同行\n"
HIW 
"           相恨不如潮有信·相思始觉海非深\n"
"\n" NOR;
}


void create()
{
        set("short", "梦湖");
        set("long", 
"在你的面前是一个小湖，湖水泛著粼光，轻柔地拍打著岸边的细沙。\n"
"透过清澈的湖水，你可以看到在水中嘻戏的鱼虾，还有随著水波婆娑起舞\n"
"的水草。岸边有一些葱葱的树木，西边是一道高耸入云的绝"CYN"壁"NOR"。\n"
);
//         set("outdoors", "chengdu");
         set("exits",([ /* sizeof() == 1 */
                 "east" : __DIR__"lakeroad",
         ]));

        set("item_desc", ([
                "绝壁": (: look_bi :),
                "壁": (: look_bi :),
                "bi": (: look_bi :),
        ]) );

                set("no_rideto", 1);
                set("no_flyto", 1);
                      set("no_magic", 1); 
        
        setup();
        
                remove_call_out("do_wave");
                call_out("do_wave", 5);        
}

int do_wave()
{
                switch(random(11)) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        tell_room(this_object(), CYN "≈≈"NOR HIG "一阵微风吹过，梦湖上面泛起了千百层粼粼碧波。\n" NOR);
                        break;
                        case 4:
                        case 5:
                        case 6:
                        tell_room(this_object(), CYN "≈≈"NOR HIW "湖水在沙滩边慢涨渐落，竟也似潮信绵绵不绝。\n" NOR);
                        break;
                        case 7:
                        case 8:
                        tell_room(this_object(), CYN "≈≈"NOR HIC "碧浪轻轻拂过沙滩，就像情人温柔地吻过你的脚趾。\n" NOR);
                        break;
                        case 9:
                        tell_room(this_object(), CYN "≈≈"NOR HIY "一个大浪打来，冲湿了青石小阶，再悄悄退却。\n" NOR);
                        break;
                case 10:
                        tell_room(this_object(), CYN "≈≈"NOR HIB "岸边树木摇曳沙沙作响，湖心岛上的木屋却安静如初。\n" NOR);
                        break;
            }
        call_out("do_wave", 30 + random(20));              
        return 1;
}

void do_open(object me)
{
        if (environment(me)!=this_object()) return;
        tell_object(me, YEL "你正思忖着，是谁用莫大的指力在石壁上刻书？\n" NOR);
        me->remove_call_out("do_open2");
        call_out("do_open2", 8, me); 
        me->remove_call_out("do_close");
        call_out("do_close", 16, me); 
}

void do_open2(object me)
{
        if (environment(me)!=this_object()) return;
        tell_object(me, YEL "绝壁突然剧烈抖动，上面的字哗哗地碎落露出一个山洞来。\n" NOR);
        set("exits/west", __DIR__"lakecave");
}

void do_close(object me)
{
        if (environment(me)!=this_object()) return;
        tell_object(me, YEL "你稍一迟疑，西面的山洞入口恢复如初。\n" NOR);
        delete("exits/west");
}




