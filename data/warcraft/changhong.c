// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("远古神兽[2;37;0m[2;37;0m", ({"qianwang"}));        
        set("gender", "男性");                
        set("long", "远古神兽[2;37;0m
它是长虹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "changhong");
        set("owner_name", "长虹");
        set_temp("owner", "changhong");
        set_temp("owner_name", "长虹");
        ::setup();
}
