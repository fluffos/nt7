// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹学[2;37;0m[2;37;0m", ({"kosxxapet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxa");
        set("owner_name", "学壹");
        set_temp("owner", "kosxxa");
        set_temp("owner_name", "学壹");
        ::setup();
}
