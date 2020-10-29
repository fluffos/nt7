// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m支付宝[2;37;0m[2;37;0m", ({"paywu"}));        
        set("gender", "男性");                
        set("long", "支付支付，不可不付！[2;37;0m
它是淘宝失误的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "taobaowu");
        set("owner_name", "淘宝失误");
        set_temp("owner", "taobaowu");
        set_temp("owner_name", "淘宝失误");
        ::setup();
}
