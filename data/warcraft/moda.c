// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m波多野结衣[2;37;0m[2;37;0m", ({"cangjk"}));        
        set("gender", "女性");                
        set("long", "波多野结衣[2;37;0m
它是莫真大的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "moda");
        set("owner_name", "莫真大");
        set_temp("owner", "moda");
        set_temp("owner_name", "莫真大");
        ::setup();
}
