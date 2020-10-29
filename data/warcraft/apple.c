// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m筷子兄弟[2;37;0m[2;37;0m", ({"apples"}));        
        set("gender", "男性");                
        set("long", "$HIG$筷子兄弟[2;37;0m
它是小平锅的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "apple");
        set("owner_name", "小平锅");
        set_temp("owner", "apple");
        set_temp("owner_name", "小平锅");
        ::setup();
}
