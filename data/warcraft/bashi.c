// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("公交车[2;37;0m[2;37;0m", ({"bus"}));        
        set("gender", "男性");                
        set("long", "新型环保公交车，主动投币，不找零钱，谢谢合作。[2;37;0m
它是巴士司机的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bashi");
        set("owner_name", "巴士司机");
        set_temp("owner", "bashi");
        set_temp("owner_name", "巴士司机");
        ::setup();
}
