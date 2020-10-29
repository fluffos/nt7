// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m坐骑[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "$BLK$坐[2;37;0m
它是照无眠的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zwm");
        set("owner_name", "照无眠");
        set_temp("owner", "zwm");
        set_temp("owner_name", "照无眠");
        ::setup();
}
