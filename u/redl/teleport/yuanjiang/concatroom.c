// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h> 

#define FILENAME "chuan"
#define NLOW 0
#define NHIGH 49


void start()
{
        object r, r2;
        int rndn;
        string r2path;
        string *exits = ({({"north", "south"}),({"south", "north"}),({"west", "east"}),({"east", "west"})});
        int *exitstmp, exitsn = sizeof(exits);
        
        for (int i = NLOW; i < NHIGH + 1; i++) {//清理
                r = get_object(__DIR__ + FILENAME + (string)i);
                destruct(r);
                r = get_object(__DIR__ + FILENAME + (string)i);
                if (!r || !objectp(r)) continue;
                delete("exits", r);
        }
        for (int i = NLOW; i < NHIGH + 1; i++) {//建路径
                r = get_object(__DIR__ + FILENAME + (string)i);
                exitstmp = ({});
                for (int i2 = 0; i2 < exitsn; i2++) {
                        if (query("exits/" + exits[i2][0], r)) continue;
                        rndn = i;
                        while (rndn==i || member_array(rndn, exitstmp)!=-1) 
                                rndn = random((NHIGH-NLOW) + 1) + NLOW;
                        r2path = __DIR__+ FILENAME + (string)rndn;
                        r2 = get_object(r2path);
                        if (query("exits/" + exits[i2][1], r2)) continue;
                        exitstmp += ({rndn});
                        set("exits/" + exits[i2][0], r2path, r);
                        set("exits/" + exits[i2][1], base_name(r), r2);
                }
        }
        //DEBUG_CHANNEL("concatroom ok!");
}



//              le = 1;
//              if (random(8)) {
//                      le += 1;
//                      if (random(3)) {
//                              le += 1;
//                              if (!random(3)) {
//                                      le += 1;
//                              }
//                      }
//              }
