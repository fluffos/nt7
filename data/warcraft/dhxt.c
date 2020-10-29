// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m洪七公[2;37;0m[2;37;0m", ({"qigong"}));        
        set("gender", "男性");                
        set("long", "$BLK$洪七公[2;37;0m
它是都会心痛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dhxt");
        set("owner_name", "都会心痛");
        set_temp("owner", "dhxt");
        set_temp("owner_name", "都会心痛");
        ::setup();
}
