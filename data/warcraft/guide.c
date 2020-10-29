// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("照狮子[2;37;0m[2;37;0m", ({"gue"}));        
        set("gender", "女性");                
        set("long", "去里马[2;37;0m
它是刘浮屠的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "guide");
        set("owner_name", "刘浮屠");
        set_temp("owner", "guide");
        set_temp("owner_name", "刘浮屠");
        ::setup();
}
