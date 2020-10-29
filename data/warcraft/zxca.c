// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹钱[2;37;0m[2;37;0m", ({"zxcapet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxca");
        set("owner_name", "钱壹");
        set_temp("owner", "zxca");
        set_temp("owner_name", "钱壹");
        ::setup();
}
