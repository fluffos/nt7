// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("黄土[2;37;0m[2;37;0m", ({"huangnitu"}));        
        set("gender", "男性");                
        set("long", "尘沙飞扬黄土地[2;37;0m
它是黄泥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "huangni");
        set("owner_name", "黄泥");
        set_temp("owner", "huangni");
        set_temp("owner_name", "黄泥");
        ::setup();
}
