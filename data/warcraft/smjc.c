// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤血麒麟[2;37;0m[2;37;0m", ({"qi_linc"}));        
        set("gender", "男性");                
        set("long", "赤血麒麟[2;37;0m
它是星宿老鬼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "smjc");
        set("owner_name", "星宿老鬼");
        set_temp("owner", "smjc");
        set_temp("owner_name", "星宿老鬼");
        ::setup();
}
