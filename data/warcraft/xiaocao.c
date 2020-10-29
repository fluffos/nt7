// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m草草[1;31m[2;37;0m[2;37;0m", ({"xiaoc"}));        
        set("gender", "女性");                
        set("long", "神兽[2;37;0m
它是小草的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaocao");
        set("owner_name", "小草");
        set_temp("owner", "xiaocao");
        set_temp("owner_name", "小草");
        ::setup();
}
