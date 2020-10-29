// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "小白虎[2;37;0m
它是凡星的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "fanxing");
        set("owner_name", "凡星");
        set_temp("owner", "fanxing");
        set_temp("owner_name", "凡星");
        ::setup();
}
