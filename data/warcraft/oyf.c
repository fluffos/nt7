// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m见证[2;37;0m[2;37;0m", ({"oyfgo"}));        
        set("gender", "男性");                
        set("long", "$HIW$见证[2;37;0m
它是哦扬风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "oyf");
        set("owner_name", "哦扬风");
        set_temp("owner", "oyf");
        set_temp("owner_name", "哦扬风");
        ::setup();
}
