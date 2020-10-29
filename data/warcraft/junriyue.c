// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m日月麒麟[2;37;0m[2;37;0m", ({"riyueql"}));        
        set("gender", "男性");                
        set("long", "日月麒麟[2;37;0m
它是君日月的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "junriyue");
        set("owner_name", "君日月");
        set_temp("owner", "junriyue");
        set_temp("owner_name", "君日月");
        ::setup();
}
