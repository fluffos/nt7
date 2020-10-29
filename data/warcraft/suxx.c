// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小晓[2;37;0m[2;37;0m", ({"suxxs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是苏小晓的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "suxx");
        set("owner_name", "苏小晓");
        set_temp("owner", "suxx");
        set_temp("owner_name", "苏小晓");
        ::setup();
}
