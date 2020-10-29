// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小腰玉麒麟[2;37;0m[2;37;0m", ({"baride"}));        
        set("gender", "男性");                
        set("long", "小腰玉麒麟[2;37;0m
它是小摇吧的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoyaoba");
        set("owner_name", "小摇吧");
        set_temp("owner", "xiaoyaoba");
        set_temp("owner_name", "小摇吧");
        ::setup();
}
