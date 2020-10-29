// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞天[2;37;0m[2;37;0m", ({"qqqq"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是风云的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wlan");
        set("owner_name", "风云");
        set_temp("owner", "wlan");
        set_temp("owner_name", "风云");
        ::setup();
}
