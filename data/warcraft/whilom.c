// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m流沙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "碧云天共楚宫遥。梦魂惯得无拘检，又踏杨花过谢桥。[2;37;0m
它是东逝水的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "whilom");
        set("owner_name", "东逝水");
        set_temp("owner", "whilom");
        set_temp("owner_name", "东逝水");
        ::setup();
}
