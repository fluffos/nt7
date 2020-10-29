// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddjj"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂级的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddj");
        set("owner_name", "堂级");
        set_temp("owner", "ddj");
        set_temp("owner_name", "堂级");
        ::setup();
}
