// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m保时捷[2;37;0m[2;37;0m", ({"xsuckjj"}));        
        set("gender", "女性");                
        set("long", "运输工具[2;37;0m
它是娘子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "suckjj");
        set("owner_name", "娘子");
        set_temp("owner", "suckjj");
        set_temp("owner_name", "娘子");
        ::setup();
}
