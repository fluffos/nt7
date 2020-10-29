// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m白猫[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "一只小猫[2;37;0m
它是风飞七扬的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "seeflyg");
        set("owner_name", "风飞七扬");
        set_temp("owner", "seeflyg");
        set_temp("owner_name", "风飞七扬");
        ::setup();
}
