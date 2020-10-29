// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多林叉麒麟[2;37;0m[2;37;0m", ({"miduoxride"}));        
        set("gender", "男性");                
        set("long", "多林叉麒麟[2;37;0m
它是米多叉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolinx");
        set("owner_name", "米多叉");
        set_temp("owner", "miduolinx");
        set_temp("owner_name", "米多叉");
        ::setup();
}
