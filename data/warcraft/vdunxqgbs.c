// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是戴雄发的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "vdunxqgbs");
        set("owner_name", "戴雄发");
        set_temp("owner", "vdunxqgbs");
        set_temp("owner_name", "戴雄发");
        ::setup();
}
