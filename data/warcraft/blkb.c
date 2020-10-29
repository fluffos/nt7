// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m张[1;31m曼[1;32m玉[2;37;0m[2;37;0m", ({"zhangmanyu"}));        
        set("gender", "女性");                
        set("long", "张曼玉（Maggie Cheung，1964年9月20日-）[2;37;0m
它是无药可救的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "blkb");
        set("owner_name", "无药可救");
        set_temp("owner", "blkb");
        set_temp("owner_name", "无药可救");
        ::setup();
}
