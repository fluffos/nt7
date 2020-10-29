// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狂疯[2;37;0m[2;37;0m", ({"kaungfeng"}));        
        set("gender", "男性");                
        set("long", "狂疯[2;37;0m
它是冷含笑的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hanxiao");
        set("owner_name", "冷含笑");
        set_temp("owner", "hanxiao");
        set_temp("owner_name", "冷含笑");
        ::setup();
}
