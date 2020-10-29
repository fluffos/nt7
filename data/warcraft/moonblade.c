// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"xiaosan"}));        
        set("gender", "男性");                
        set("long", "远古溶洞诞生的一头异兽[2;37;0m
它是圆月弯刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "moonblade");
        set("owner_name", "圆月弯刀");
        set_temp("owner", "moonblade");
        set_temp("owner_name", "圆月弯刀");
        ::setup();
}
