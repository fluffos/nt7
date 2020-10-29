// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赤兔马[2;37;0m[2;37;0m", ({"chitu"}));        
        set("gender", "女性");                
        set("long", "这马不好老偷懒[2;37;0m
它是红烧肥肠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hsfc");
        set("owner_name", "红烧肥肠");
        set_temp("owner", "hsfc");
        set_temp("owner_name", "红烧肥肠");
        ::setup();
}
