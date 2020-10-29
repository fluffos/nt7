// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m鲲鹏[2;37;0m[2;37;0m", ({"flying"}));        
        set("gender", "男性");                
        set("long", "北冥有鱼,其名为鲲,鲲之大,不知其几千里也[2;37;0m
它是不拜天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "freedom");
        set("owner_name", "不拜天");
        set_temp("owner", "freedom");
        set_temp("owner_name", "不拜天");
        ::setup();
}
