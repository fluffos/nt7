// Room: /d/shaolin/bagua.h
// Date: YZC 96/01/19

string* dirs = ({
        "坎", "坤", "离", "乾",
        "艮", "震", "巽", "兑"
        });

int check_dirs(object me, string dir)
{
        int i, bc, count;
        if (member_array(dir, dirs) != -1)
        {
                bc=query_temp("bagua/count", me);

                switch (dir)
                {
                case "坎":
                        if (bc == 0 || bc == 13 || bc == 17) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_damage("jing",50); }                        
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "坤":
                        delete_temp("bagua/count", me);
                        break;
                case "离":
                        if (bc == 1 || bc == 12 ) {
                                set_temp("bagua/count", bc+1, me);
                                addn("neili", -50, me);}
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "乾":
                        if (bc == 8 ) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_damage("qi", 50); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "艮":
                        if (bc == 3 || bc == 4 || bc == 15) {
                                set_temp("bagua/count", bc+1, me);
                                addn("combat_exp", -50, me);}
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "震":
                        if (bc == 2 || bc == 7 || bc == 9 ) {
                                set_temp("bagua/count", bc+1, me);
                                me->unconcious(); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "巽":
                        if (bc == 6 || bc == 11 ) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_wound("qi", 50); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "兑":
                        if (bc == 5 || bc == 10 || bc == 14 || bc == 16) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_wound("jing", 50); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                default:
                        delete_temp("bagua/count", me);
                        break;
                }

                if (dir == "坤")
                {
                        delete_temp("bagua", me);
                }
                else
                {
                        count=query_temp("bagua/"+dir, me);
                        count++;
                        set_temp("bagua/"+dir, count, me);
                        if (count > 13)
                        {
                                delete_temp("bagua", me);
                                me->move(__DIR__"jianyu");
                                return (1);
                        }
                }
        }

/*
        write("*"+query_temp("bagua/northwest", me));
        write(""+query_temp("bagua/north", me));
        write(""+query_temp("bagua/northeast", me)+"\n");
        
        write("*"+query_temp("bagua/west", me));
        write(""+query_temp("bagua/count", me));
        write(""+query_temp("bagua/east", me)+"\n");
        
        write("*"+query_temp("bagua/southwest", me));
        write(""+query_temp("bagua/south", me));
        write(""+query_temp("bagua/southeast", me)+"\n");
*/
        return (0);
}