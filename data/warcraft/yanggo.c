// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m世京[2;37;0m[2;37;0m", ({"yanggogo"}));        
        set("gender", "女性");                
        set("long", "$HIW$世京[2;37;0m
它是扬锅的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yanggo");
        set("owner_name", "扬锅");
        set_temp("owner", "yanggo");
        set_temp("owner_name", "扬锅");
        ::setup();
}
