// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

string look_xiang(object me)
{
        string snum;
        mapping cg_teachers = ([]);
        if (me->is_busy()) return NOR"你现在正忙。\n"NOR;
        me->start_busy(3);
        cg_teachers = query("cg_teachers");
        if (undefinedp(cg_teachers) || !mapp(cg_teachers) || !sizeof(cg_teachers))
          snum = "没有主人";
         else 
          snum = "有" + chinese_number(sizeof(cg_teachers)) + "人";
        return NOR "温馨提示：现在" + snum + "在此拓印下武学。\n主人上楼来会自动拓印(要求１００亿经验、５００万潜能)，任何人上楼来都有机会学习，注意９０秒超时。\n" NOR;
}


void create()
{
        set("short", "二楼");
        set("long", 
"这里是传功楼的二楼，房间正中有一尊神龛，供奉着个西瓜大小的水晶\n"
"头颅("CYN"skull"NOR")。颅骨上无数玄奥的蝌蚪文在游动，金色的紫焰在它的七窍间升\n"
"腾着钻进钻出。\n"
);
                //set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "down" : __DIR__"chuangonglou",
                ]));

        set("item_desc", ([
                "skull": (: look_xiang :),
        ]) );
        
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,1);
        //set("owner_level", 1);
        
        setup();
}

int ta_skills(object gcroom, object me)
{
        mapping mycgsk = ([]), cg_teachers = ([]);
        mapping newskls, skls = me->query_skills();
        mapping newpfms, pfms = query("can_perform", me);
        mapping teacher;
        string *vskls = ({});
        int flag = 1;
        
        if (undefinedp(skls) || !mapp(skls) || !sizeof(skls))
                return 0;
        
        mycgsk = query("dongtian/cg_data/skills_id", me);       
        foreach (string tmpskn in keys(skls)) {
                if (skls[tmpskn] < 800) vskls += ({tmpskn});
                else if (mycgsk || mapp(mycgsk) || sizeof(mycgsk)) {
                        if (member_array(tmpskn, keys(mycgsk))!=-1) {
                                vskls += ({tmpskn});
                        }
                }
        }
        newskls = copy(skls);
        newpfms = copy(pfms);
        foreach (string tmpskn2 in vskls) {
                //write(tmpskn2 + "\n");
                map_delete(newskls, tmpskn2);
                map_delete(newpfms, tmpskn2);
        }
        
        teacher = ([
                "id"    :       query("id", me),
                "name"  :       query("name", me),
                "guid"  :       query("hold_time", gcroom),
                "skills":       newskls,
                "can_perform":  newpfms,
                ]);

        cg_teachers = __DIR__"data.c"->do_load("cg_teachers");
        set("cg_teachers",  cg_teachers);
        
        set("cg_teachers/" + query("id", me),  teacher);
        cg_teachers = query("cg_teachers");
        __DIR__"data.c"->do_save("cg_teachers", cg_teachers);
        

        write(NOR + "你拓印下了这些技能在此：[\n" + NOR + CYN + sort_msg(implode(map_array(keys(newskls),(: to_chinese($1) :)),"、"),30) + "]\n" + NOR);

        write(NOR CYN "水晶头颅" YEL "上的两个空洞的眼眶喷出金光对着你一卷..\n你感觉修到８００级的技能被搜了一遍，浑身一阵虚脱无力。\n" NOR "( 你的战斗经验减少２０００万，潜能减少５００万 )\n");
        addn("potential", -5000000, me);
        addn("combat_exp", -20000000, me);
        set("dongtian/chuangong/ta_time", time() + 86400, me);
        return 1;
}

int do_nod(string arg)
{
        object me = this_player();
        mapping cg_data, mypfms, mysks;
        string delskill, stmp;
        int idelskill, itmp, skmax;
        object hu, gcroom = get_object(__DIR__"guangchang.c");
        
        if (!arg || arg!="skull") {
                write(NOR + "你想答应谁？\n" + NOR);
                return 1;
        }

        if (me->is_busy()) {
                write(NOR + "你现在正忙。\n" + NOR);
                return 1;
        }
        
        me->start_busy(3);
        
        if (query_temp("teacher/studentid")!=query("id", me) || (this_object() != environment(me))) {
                write(NOR + "点啥头？关你屁事啊...\n" + NOR);
                return 1;
        }
        
        delskill = query_temp("teacher/delskill");
        idelskill = me->query_skillo(delskill, 1);
        if ( idelskill < 2000 ) {
                write(NOR + "你的供奉技能的等级未合要求，脱掉全部装备再来。\n" + NOR);
                return 1;
        }

        cg_data = query("dongtian/cg_data", me);
        if (!undefinedp(cg_data) || cg_data || mapp(cg_data) || sizeof(cg_data)) {
                write(NOR + "你不能再从传功楼学新技能了，除非使用白玉笏<use baiyu hu>放弃掉。\n" + NOR);
                return 1;
        }
        
        hu = query_temp("handing", me);//白玉笏定价200，不能过低，免于大米学习泛滥和利用
        if (!hu || base_name(hu)!="/d/dongtian/obj/baiyuhu") {
                write(NOR + "你手里必须握有白玉笏<hand hu>。\n" + NOR);
                return 1;
        }
        
        cg_data = ([
                "guid"                  :               query_temp("teacher/guid"),
                "teacher_name"  :               query_temp("teacher/name"),
                "teacher_id"    :               query_temp("teacher/id"),
                "skills_name"   :               query_temp("teacher/skillsname"),
                "skills_id"             :               query_temp("teacher/skills"),
                "can_perform"   :               query_temp("teacher/can_perform"),
                "center"                :               __DIR__"guangchang.c",
        ]);
        
        message_vision(NOR + YEL + "$N" + NOR + YEL + "重重地对着" + CYN + "水晶头颅" + YEL "点了点头。\n" + NOR, me);
        
        mysks = cg_data["skills_id"];
        skmax = to_int(pow(to_float(query("combat_exp", me)/100), 1.0 / 3)*10) + 1; 
        foreach(stmp in keys(mysks)) {
                 itmp = mysks[stmp];
                 if (itmp > skmax) itmp = skmax;
                 me->set_skill(stmp, itmp);
                 message_vision(NOR + YEL + "无数金色蝌蚪文涌向$N" + NOR + YEL + "的头顶，$N" + 
                        NOR + YEL + "的『" + NOR + CYN + to_chinese(stmp) + NOR + YEL + "』提高到" + NOR + CYN + (string)itmp + NOR + YEL + "级了。\n" + NOR, me);
                 CHANNEL_D->channel_broadcast("dt", NOR + HIW + "听说" + query("name", me) + NOR + HIW + "在" + 
                        NOR + HIC + __DIR__"guangchang.c"->load_name() + NOR + HIW + 
                        "洞天的传功楼学会了『" + NOR + CYN + to_chinese(stmp) + NOR + HIW + "』。\n" + NOR);
        }
        
        mypfms = cg_data["can_perform"];
        if (mypfms && sizeof(mypfms)) foreach(stmp in keys(mypfms)) {
                 set("can_perform/" + stmp, mypfms[stmp], me);
                 message_vision(NOR + "$N" + NOR + "习得了『" + NOR + CYN + to_chinese(stmp) + NOR + "』的一些绝招。\n" + NOR, me);
        }
        
        me->delete_skill(delskill); 
        write(NOR "你忘记了关于『" + NOR + CYN + to_chinese(delskill) + NOR + "』的所有内容(不包括绝招)。\n" NOR);
        gcroom->cg_add(me);

        set("dongtian/cg_data", cg_data, me);
        destruct(hu);
        gcroom->add_qy2(20000);
        write(NOR HIY "洞天气运 +２００００。\n" NOR);
        write(NOR CYN "你耳边传来重重一声叹息道：下去吧，以后少来这里。\n" NOR);
        message_vision(append_color(NOR + YEL + "虚空中穿过来一只大如山岳的巨掌，按着$N" + NOR + YEL + "往楼下一推。\n" + NOR, YEL), me);
        me->move(query("exits/down"));
        message_vision(NOR + YEL + "一阵金烟弥散过后，$N" + NOR + YEL + "从楼梯上骨碌骨碌滚了下来。\n" + NOR, me);
        me->save();
        log_file("static/dongtiancg", ctime(time()) + " 传功 " + query("id", me) + " \n");
        return 1;
}

int tra_skills2(object gcroom, object me)
{
                write(NOR CYN "水晶头颅继续说道：\n"
                        "  你拥有这次学到的技能后，将会掌握和原主人拓印时一样的绝招。\n"
                        "  学到以后，每次再见到我，都可以更新技能到它的主人拓印下的程度。\n"
                        "  今后不能再从传功楼学新技能了，除非使用白玉笏<use baiyu hu>放弃掉。\n"
                        "  假如本洞天失守，你学到的技能和绝招，将会被我无条件地抹去。\n"
                        "  你还愿意吗？\n"
                         +  NOR + "( 答应的话输入<nod skull>，需要手里握着白玉笏 )\n" + NOR + 
                         BLINK + HIR + "重要提示：脱下你所有的加技能的装备，不要自误。\n" + NOR);
        return 1;
}

int tra_skills(object gcroom, object me)
{
        mapping cg_teachers = ([]);
        mapping teacher;
        mapping cg_data;
        mapping setpfms, setskills, newtskls, tskls, skls = copy(me->query_skills());
        int sflag = 1, tmpi, inum = 5;
        string *tmpkeys, delskill, *tsks = ({});
        int itmp, skmax;
        
        cg_teachers = copy(query("cg_teachers"));
        
        if (undefinedp(cg_teachers) || !mapp(cg_teachers) || !sizeof(cg_teachers))
                return 0;
        if (undefinedp(skls) || !mapp(skls) || !sizeof(skls))
                return 0;
                
        delete_temp("teacher"); 
        
        cg_data = query("dongtian/cg_data", me);
        if (undefinedp(cg_data) || !mapp(cg_data) || !sizeof(cg_data)) {//新学拓印
                while(sizeof(cg_teachers) && sflag) {
                        teacher = values(cg_teachers)[random(sizeof(cg_teachers))];
                        if (query("id", me)!=teacher["id"]) {
                                sflag = 0;
                                break;
                        }
                        map_delete(cg_teachers, teacher["id"]);
                }
                if (sflag) {
                        write(NOR "目前没小伙伴可以教你，而你又不能自己教自己。\n" NOR);
                        return 0;//唯一合格的teacher是自己
                }
                if (gcroom->owner_level(me)>1) inum += 2;
                write(NOR + "你这次的师傅是" + teacher["name"] + "，最多可以学到" + chinese_number(inum) + "样技能。\n" + NOR);
                tskls = teacher["skills"];
                if (undefinedp(tskls) || !mapp(tskls) || !sizeof(tskls)) return 0;
                newtskls = copy(tskls);
                foreach(string tmptsk in keys(tskls)) {
                        if ( me->query_skillo(tmptsk, 1)>0 ) {
                                //write("本来已会:" + tmptsk + "\n");
                                map_delete(newtskls, tmptsk);
                        } /*else {
                                write(HIY + "不会:" + tmptsk + "\n" + NOR);
                        }*/
                }
                setskills = ([]);
                while (inum-- && sizeof(newtskls)) {
                        tmpi = random(sizeof(newtskls));
                        setskills += ([ copy(keys(newtskls)[tmpi]) : copy(values(newtskls)[tmpi]) ]);
                        tsks += ({ to_chinese(copy(keys(newtskls)[tmpi])) });
                        //write(HIC + "添加:" + keys(newtskls)[tmpi] + "\n" + NOR);
                        map_delete(newtskls, keys(newtskls)[tmpi]);
                }
                if (!setskills || !sizeof(setskills)) {
                        write(NOR + teacher["name"] + "会的技能你都会，没办法学习。\n" + NOR);
                        return 0;
                }
                        
                sflag = 1;
                while(sizeof(skls) && sflag) {
                        delskill = keys(skls)[random(sizeof(skls))];
                        if (skls[delskill]>=2000) {
                                sflag = 0;
                                break;
                        }
                        map_delete(skls, delskill);
                }
                if (sflag) {
                        write(NOR + "你连一样大于２０００的技能都没有，没办法供奉给水晶头颅。\n" + NOR);
                        return 0;//没有够等级的供奉skill
                }
                        
                setpfms = copy(teacher["can_perform"]);
                tmpkeys = copy(keys(setpfms));
                foreach(string tmptsk2 in tmpkeys) {
                        if (undefinedp(setskills[tmptsk2]) || !setskills[tmptsk2])
                        map_delete(setpfms, tmptsk2);
                }

                set_temp("teacher/skills", setskills);
                set_temp("teacher/skillsname", tsks);
                set_temp("teacher/id", teacher["id"]);
                set_temp("teacher/studentid", query("id", me));
                set_temp("teacher/name", teacher["name"]);
                set_temp("teacher/guid", teacher["guid"]);
                set_temp("teacher/can_perform", setpfms);
                set_temp("teacher/delskill", delskill);
                write(NOR CYN "水晶头颅" HIG "传递神念给你：你可愿意把『" + HIY + to_chinese(query_temp("teacher/delskill")) + HIG + 
                        "』供奉给我？我可以传授你" + query_temp("teacher/name") + "拓印\n在这的『" + NOR + HIY + 
                        implode(tsks, HIG + "』『" + NOR + HIY) + HIG + "』。\n" + 
                         NOR + "( 答应的话输入<nod skull>，需要手里握着白玉笏 )\n" + NOR);
                remove_call_out("tra_skills2");
                call_out("tra_skills2", 2, gcroom, me);
        } else {//更新拓印
                teacher = copy(cg_teachers[cg_data["teacher_id"]]);
                setskills = copy(cg_data["skills_id"]);

                if (undefinedp(teacher) || !mapp(teacher) || !sizeof(teacher))
                        return 0;
                if (undefinedp(setskills) || !mapp(setskills) || !sizeof(setskills))
                        return 0;

                tskls = teacher["skills"];
                if (undefinedp(tskls) || !mapp(tskls) || !sizeof(tskls)) return 0;

                foreach(string tmptsk3 in keys(setskills)) {
                        itmp = tskls[tmptsk3];
						skmax = to_int(pow(to_float(query("combat_exp", me)/100), 1.0 / 3)*10) + 1; // mud modified
                        if ( me->query_skillo(tmptsk3, 1)<itmp ) {
if (itmp > skmax && SKILL_D(tmptsk3)->type() == "martial") itmp = skmax; //mud modified
                                 me->set_skill(tmptsk3, itmp);
                                 message_vision(NOR + YEL + "无数金色蝌蚪文涌向$N" + NOR + YEL + "的头顶，$N" + 
                                        NOR + YEL + "的『" + NOR + CYN + to_chinese(tmptsk3) + NOR + YEL + "』提高到" + NOR + CYN + (string)itmp + NOR + YEL + "级了。\n" + NOR, me);
                        } 
                        if (teacher["can_perform"][tmptsk3]) {
                                set("can_perform/" + tmptsk3, teacher["can_perform"][tmptsk3], me);
                                message_vision(NOR + "$N" + NOR + "更新了『" + NOR + CYN + to_chinese(tmptsk3) + NOR + "』的一些绝招。\n" + NOR, me);
                        }
                }

                
        }
                
        
        
        return 1;
}

int push_down(object me)
{
        mapping cg_data;
        
        if (!me) return 1;
        if (!environment(me)) return 1;
        if (environment(me)!=this_object()) return 1;
        
        cg_data = query("dongtian/cg_data", me);
        if (undefinedp(cg_data) || !mapp(cg_data) || !sizeof(cg_data)) {
                tell_object(me, NOR CYN "你耳边传来重重一声叹息道：下去吧，畏首畏尾，瞻前顾后的鼠辈。\n" NOR);
        } else {
                tell_object(me, NOR CYN "你耳边传来重重一声叹息道：时间到了，别占着茅坑不拉屎，下去吧。\n" NOR);
        }
        message_vision(append_color(NOR + YEL + "虚空中穿过来一只大如山岳的巨掌，按着$N" + NOR + YEL + "往楼下一推。\n" + NOR, YEL), me);
        me->move(query("exits/down"));
        message_vision(NOR + YEL + "一阵金烟弥散过后，$N" + NOR + YEL + "从楼梯上骨碌骨碌滚了下来。\n" + NOR, me);
        return 1;
}

void init()
{
        object gcroom = get_object(__DIR__"guangchang.c");
        object ob, *obs, me = this_player();
        
        if (!playerp(me)) return;
        
                                obs = filter_array(all_inventory(me),
                           (: query("equipped", $1) :));

        if (obs && arrayp(obs) && sizeof(obs) && wiz_level(me) < 5) {
                write(NOR "你这么不听劝，身上怎么还戴有装备？\n" NOR);
                push_down(me);
                return;
        }
        
 if (query("hold_time", gcroom) > 1) {//洞天玩家所有时
        set("dongtian/chuangong/visit_time", time() + 300, me);
        if (gcroom->owner_level(me) > 1 && (query("potential", me)-query("learned_points", me))>5000000 && query("combat_exp",me)>10000000000 && query("dongtian/chuangong/ta_time", me)<time()) {
                ta_skills(gcroom, me);
        } else {
                set("cg_teachers",  __DIR__"data.c"->do_load("cg_teachers"));
        }

        me->start_busy(6);
        add_action("do_nod", "nod");
        remove_call_out("tra_skills");
        call_out("tra_skills", 2, gcroom, me);
 }

        remove_call_out("push_down");
        call_out("push_down", 90, me);
        ::init();
}



