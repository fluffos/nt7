// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白猫[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "上古神兽白虎化成了一只可爱的小白猫。[2;37;0m
它是降龙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "delphi");
        set("owner_name", "降龙");
        set_temp("owner", "delphi");
        set_temp("owner_name", "降龙");
        ::setup();
}
