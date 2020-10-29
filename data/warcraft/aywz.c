// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "好吃懒做[2;37;0m
它是诸葛瑾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "aywz");
        set("owner_name", "诸葛瑾");
        set_temp("owner", "aywz");
        set_temp("owner_name", "诸葛瑾");
        ::setup();
}
