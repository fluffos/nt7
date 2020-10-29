// REDGIRL.C
#include <ansi.h>
inherit NPC;
void create()
{       
        set_name("小香", ({ "xiang" }) );
        set("long", "这是一个美丽的少女，但眉眼中却蕴着淡淡的忧伤。\n");
        set("age", 16);
        set("gender", "女性");
        set("attitude", "peaceful");
        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}
