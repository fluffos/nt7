// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("风卷[2;37;0m[2;37;0m", ({"fengjuan"}));        
        set("gender", "女性");                
        set("long", "风卷[2;37;0m
它是风卷楼残的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "loucan");
        set("owner_name", "风卷楼残");
        set_temp("owner", "loucan");
        set_temp("owner_name", "风卷楼残");
        ::setup();
}
