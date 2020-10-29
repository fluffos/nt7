// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁钱[2;37;0m[2;37;0m", ({"zxccpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxcc");
        set("owner_name", "钱叁");
        set_temp("owner", "zxcc");
        set_temp("owner_name", "钱叁");
        ::setup();
}
