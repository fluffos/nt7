// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m啸天犬[2;37;0m[2;37;0m", ({"langquan"}));        
        set("gender", "男性");                
        set("long", "啸天犬[2;37;0m
它是小鱼儿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoyuer");
        set("owner_name", "小鱼儿");
        set_temp("owner", "xiaoyuer");
        set_temp("owner_name", "小鱼儿");
        ::setup();
}
