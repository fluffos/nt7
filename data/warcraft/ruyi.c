// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玉兔[2;37;0m[2;37;0m", ({"yutu"}));        
        set("gender", "女性");                
        set("long", "这就是月宫中的小白兔。[2;37;0m
它是如意的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ruyi");
        set("owner_name", "如意");
        set_temp("owner", "ruyi");
        set_temp("owner_name", "如意");
        ::setup();
}
