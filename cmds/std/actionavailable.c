// actionavailable.c

#include <ansi.h>
#include <weapon.h>
#include <login.h>
inherit F_CLEAN_UP;

int room_path(object, object);
int user_path(object, object);

int main(object me, string arg)
{
        object ob, *inv;
        string win,*ids;

        if (! arg || sscanf(arg, "%s,%s", arg, win) != 2)
                return 0;

        switch (win)
        {
                case "0" :
                        ob=present(arg,environment(me));
                        if(!objectp(ob)) {
                                inv=all_inventory(environment(me));
                                for(int i = 0; i<sizeof(inv); i++) {
                                        if(inv[i]==me) continue;
                                        if( ids=query_temp("apply/id", inv[i]) )
                                        for(int j=0;j<sizeof(ids);j++) {
                                                if(ids[j]==arg)
                                                ob=inv[i];
                                        }
                                }
                        }
                        room_path(me,ob);
                        break;
                case "1" :
                        ob=present(arg,me);
                        user_path(me,ob);
                        break;
        }
        return 1;
}

int room_path(object me, object ob)
{
        mapping skills,meskills;
        object *inv;
        string *str,*ids;
        string id,name,tmp;
        int i,my_skill;

        if(!objectp(ob)) return 1;

        if(stringp(tmp=ob->query_menu(me,0)))//如果对象能解释菜单，则直接返回菜单
        {
                write(tmp);
                return 1;
        }


        if( !query("apply/id", ob))id=query("id", ob);
        else {
                ids=query_temp("apply/id", ob);
                id=ids[sizeof(ids)-1];
        }

//      if(ob->query_temp("apply/name")) name=ob->query_temp("apply/name");
        tmp=TMI("mbegin "+ob->name(1)+";"+id)+TMI("mitem 观察$U;look "+id);
        if(living(ob))
        {
                if(interactive(ob))
                {
                        tmp+=TMI("mitem 告诉$U...;tell "+id+" ...")+TMI("mitem 对$U耳语...;whisper "+id+" ...");
                        if( id == query_temp("reply", me) )
                                write(TMI("mitem 回答$U...;reply ..."));
                }
                if( query("ridable", ob) )
                {
                        tmp+=TMI("mitem 骑上$U;ride "+id);
                }

                tmp+=(me->query_leader()==ob)?TMI("mitem 停止跟随$U;follow none"):TMI("mitem 跟随$U;follow "+id);
                if( !query("no_fight", environment(me)) )
                {
                        tmp+=TMI("mitem 与$U切磋;fight "+id);
                        if( query("age", ob)>17 || !interactive(ob) )
                                tmp+=TMI("mitem 攻击$U;hit "+id)+TMI("mitem 杀死$U;kill "+id)+TMI("mitem 偷袭$U;touxi "+id)+TMI("mitem 偷$U的...;steal ... from "+id);
                }
                if( query("inquiry", ob)){
                        str=keys(query("inquiry", ob));
                        for(i=0; i<sizeof(str); i++)
                                tmp+=TMI("mitem 向$U打听关于"+str[i]+"的信息;ask "+id+" about "+str[i]+"");
                }
                tmp+=TMI("mitem 给$U...东西;give ... to "+id );
                if( query("owner", ob) == query("id", me) )
                {

                        if( query("magic/become", ob) )
                        {
                                if( query_temp("is_changing", me) )
                                {
                                        tmp+=TMI("mitem 解除-->〖铠化〗 ;recall recover "+id+"");
                                }
                                else
                                {
                                        tmp+=TMI("mitem 幻兽-->〖铠化〗 ;recall change "+id+"");
                                }

                        }
                        if( query("magic/owner", ob) )
                        {
                                tmp+=TMI("mitem 供能-->〖$U〗 ;upgrade "+id+"");

                        }
                        // tmp+=TMI("mitem 教导-->〖$U〗 ;teach "+"...");
                        // tmp+=TMI("mitem 技能-->〖$U〗 ;skills "+id+"");
                }
                if( query("family/family_name", me) == "丐帮"){
                        if ( me->query_skill("checking",1) >= 10 )
                                tmp+=TMI("mitem 打探...的技能;check ...");
                        if( query("family/family_name", ob) != "丐帮" )
                                tmp+=TMI("mitem 乞讨$U的...;beg ... from "+id);
                }
                if( query("vendor_goods", ob)){
                        tmp+=TMI("mitem 查询$U出售的东西;list "+id+"");
                        tmp+=TMI("mitem 向$U买...;buy ...");
                }
                if( query("dealer", ob) == "pawn"){
                        if( !query("vendor_goods", ob)){
                                tmp+=TMI("mitem 查询$U出售的东西;list");
                                tmp+=TMI("mitem 向$U买...;buy ...");
                        }
                        tmp+=TMI("mitem 估价...;value ...");
                        tmp+=TMI("mitem 卖...给$U;sell ...");
                        tmp+=TMI("mitem 典当...给$U;pawn ...");
                        if( query("pawns", me) )
                                tmp+=TMI("mitem 赎回物品...;redeem ...");
                }
                if( query("dealer", ob) == "bank"){
                        tmp+=TMI("mitem 兑换货币;convert ...");
                        tmp+=TMI("mitem 存钱;deposit ...");
                        if( query("balance", me)){
                                tmp+=TMI("mitem 查询存款;check");
                                tmp+=TMI("mitem 取钱;withdraw ...");
                        }
                }
                if( query("family/master_name", me) != ob->name(1)){
                        if(ob->is_master())
                                tmp+=TMI("mitem 拜$U为师;bai "+id);
                } else {
                        tmp+=TMI("mitem 向师父$U磕头;bai "+id);
                        tmp+=TMI("mitem 查询师父$U技能;skills "+id);
                        if( ob->query_skills() && query("jing", me) >= 1
                                 && query("potential", me)>query("learned_points", me)){
                                skills=ob->query_skills();
                                str=keys(skills);
                                for(i=0; i<sizeof(str); i++) {
                                        if(me->query_skills()) {
                                                meskills=me->query_skills();
                                                my_skill = me->query_skill(str[i], 1);
                                                if( (string)SKILL_D(str[i])->type()=="martial"
                                                         && my_skill*my_skill*my_skill/10>query("combat_exp", me) )
                                                        continue;
                                                if(skills[str[i]]>my_skill && str[i]!="idle")
                                                        tmp+=TMI("mitem 学习"+to_chinese(str[i])+";learn "+id+" "+str[i]+" ...");
                                        } else
                                        tmp+=TMI("mitem 学习"+to_chinese(str[i])+";learn "+id+" "+str[i]+" ...");
                                }
                        }
                }
        } else {
                if( !query("no_get", ob) )
                        tmp+=TMI("mitem 把$U捡起来;get "+id);
                if(ob->is_container()) {
                        inv = all_inventory(ob);
                        if(sizeof(inv)) {
                                tmp+=TMI("mitem 把$U里的东西都拿出来;get all from "+id);
                                tmp+=TMI("mitem 从$U里拿出...;get ... from "+id);
                        }
                        tmp+=TMI("mitem 把...装进$U里;put ... in "+id);
                }
                if(id=="board") {
                        tmp+=TMI("mitem 读新的留言;read new");
                        tmp+=TMI("mitem 读第...条留言;read ...");
                        tmp+=TMI("mitem 写新的留言;post ...");
                        tmp+=TMI("mitem 删除留言...;discard ...");
                }
        }
        tmp+=TMI("mendd");
        tell_object(me,tmp);
        return 1;
}

int user_path(object me, object ob)
{
        mapping prop;
        string id,tmp;

        if(!objectp(ob)) return 1;

        if(stringp(tmp=ob->query_menu(me,1)))//如果对象能解释菜单，则直接返回菜单
        {
                write(tmp);
                return 1;
        }

        id=query("id", ob);
        tmp=TMI("mbegin "+ob->name(1)+";"+id)+TMI("mitem 观察$U;look "+id);

        if( !query("no_drop", ob) )
                tmp+=TMI("mitem 丢弃$U;drop "+id);

        if( !query("no_give", ob) )
                tmp+=TMI("mitem 把$U给...;give "+id+" to ...");

        if( query("ridable", ob) && query_temp("is_rided_by", ob) == me && 
           query_temp("is_riding", me) == ob )
        {
                tmp+=TMI("mitem 跳下$U;unride "+id);
        }

        if( query("liquid", ob)){
                if( query("liquid/remaining", ob) )
                        tmp+=TMI("mitem 喝$U;drink "+id);
                if( query("resource/water", environment(me)) )
                        tmp+=TMI("mitem 把$U装满水;fill "+id);
        }

        if( query("food_remaining", ob) )
                tmp+=TMI("mitem 吃$U;eat "+id);

        if(ob->is_container()) {
                tmp+=TMI("mitem 把$U里的东西都拿出来;get all from "+id);
                tmp+=TMI("mitem 从$U里拿出...;get ... from "+id);
                tmp+=TMI("mitem 把...装进$U里;put ... in "+id);
        }
        if(mapp(prop=query("armor_prop",ob)) && stringp(query("armor_type", ob)) ) {
                if( !query("equipped", ob) )
                        tmp+=TMI("mitem 穿上$U;wear "+id);
                else
                        tmp+=TMI("mitem 脱下$U;remove "+id);
        }

        if(mapp(prop=query("weapon_prop", ob)) && stringp(query("skill_type", ob))) {
                if( !query("equipped", ob) )
                        tmp+=TMI("mitem 装备$U;wield "+id);
                else
                        tmp+=TMI("mitem 解除装备$U;unwield "+id);
        }

        if( query("skill", ob) )
                tmp+=TMI("mitem 读$U;study "+id);

        // "幻兽笛使用列表
        if(id=="shou shao")
        {
                if( query("can_whistle", me) )
                {
                        string *huanshou_str;

                        huanshou_str=keys(query("can_whistle", me));
                        if( query_temp("pet_id", me) )
                        {
                                tmp+=TMI("mitem 驱使〖攻击〗 ;attack "+"...");
                                tmp+=TMI("mitem 停止〖攻击〗 ;stop "+huanshou_str[0]+"");
                                tmp+=TMI("mitem 查看〖幻兽〗 ;shape "+huanshou_str[0]+"");
                                tmp+=TMI("mitem 召回〖幻兽〗 ;whistle "+huanshou_str[0]+"");
                        }
                        else
                        {
                                tmp+=TMI("mitem 召唤〖幻兽〗 ;whistle "+huanshou_str[0]+"");
                        }
                                // tmp+=TMI("mitem 描述〖幻兽〗 ;modify "+huanshou_str[0]+"");
                        if( query_temp("beastdied", me) )
                        {
                                tmp+=TMI("mitem 复活〖幻兽〗 ;recall reborn "+huanshou_str[0]+"");
                        }
                }
        }
        //毒药使用加强
        if( query("poison_type", ob) == "poison" )
        {
                if( query("can_pour", ob) )
                        tmp+=TMI("mitem 在〖容器〗中淬毒 ;pour "+id+" in ...");
                if( query("can_drug", ob) )
                        tmp+=TMI("mitem 在〖食物〗中淬毒 ;drug "+id+" in ...");
                if( query("can_daub", ob) )
                {
                        tmp+=TMI("mitem 在〖武器〗上淬毒 ;daub "+id+" on ...");
                        tmp+=TMI("mitem 在〖防具〗上淬毒(危险) ;daub "+id+" on ...");
                        tmp+=TMI("mitem 在〖手上〗上淬毒(危险) ;daub "+id+" on hand ...");
                }
        }
        tmp+=TMI("mendd");
        tell_object(me,tmp);
        return 1;
}
