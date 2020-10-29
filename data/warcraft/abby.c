// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m黑羽流星[2;37;0m[2;37;0m", ({"dvil"}));        
        set("gender", "男性");                
        set("long", "神兽[2;37;0m
它是苍羽流星的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "abby");
        set("owner_name", "苍羽流星");
        set_temp("owner", "abby");
        set_temp("owner_name", "苍羽流星");
        ::setup();
}
