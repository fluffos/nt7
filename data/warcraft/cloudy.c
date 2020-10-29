// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m棉花糖[2;37;0m[2;37;0m", ({"tigger"}));        
        set("gender", "男性");                
        set("long", "白乎乎的一团，可别被它的表面所蒙蔽。战斗状态可是威风凛凛滴.[2;37;0m
它是任云飞的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cloudy");
        set("owner_name", "任云飞");
        set_temp("owner", "cloudy");
        set_temp("owner_name", "任云飞");
        ::setup();
}
