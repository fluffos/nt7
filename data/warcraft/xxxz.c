// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星秀麒麟[2;37;0m[2;37;0m", ({"xxxzride"}));        
        set("gender", "男性");                
        set("long", "星秀麒麟[2;37;0m
它是星绣小子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xxxz");
        set("owner_name", "星绣小子");
        set_temp("owner", "xxxz");
        set_temp("owner_name", "星绣小子");
        ::setup();
}
