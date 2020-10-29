// Code of ShenZhou
// lt_snake.c 两头蛇 ( ??? )
// by maco

#include <ansi.h>

inherit SNAKE;

int auto_perform_double();

void create()
{
        int poison = 10;
        set_name("两头蛇", ({ "liangtou she", "she", "snake" }) );
        set("age", 100);
        set("long", "这条蛇花纹斑斓，颈子两边分岔，竟然有两个头，极是狰狞。\n据说看到两头蛇的人，一定会死。\n");
        set("attitude", "aggressive");

        set_weight(poison*600 + 9000);
        set("str", 30 + poison );
        set("con", 30 + poison );
        set("int", 20);
        set("dex", 30 + poison );

        set("max_jing", 9000);
        set("max_qi", 9000);
        set("max_jingli", 9000);

        set("limbs", ({ "左颈", "右颈", "身体", "七寸", "尾巴" }) );

        set("combat_exp", 1200000);

        set_temp("apply/attack", 700);
        set_temp("apply/damage", 250);
        set_temp("apply/dodge", 200);
        set_temp("apply/armor", 300);

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: auto_perform_double :),
        }));

        set("snake_poison", ([
                "level"  : 45,
                "perhit" : 25,
                "remain" : 45,
                "maximum": 45,
                "supply" : 2,
        ]));

        set("bt_snake", 1);

        setup();
}


#include "snake_perform.h"