#include <ansi.h>
#define TOTALRATE       1000
inherit COMBINED_ITEM;

int open_baoxiang(object me,object this);
string test(object me,object this);

string extra_long() 
{
        string str;
        mixed key,list;
        object ob;
        int i;
        str = this_object()->name()+"中可能开出的奖励包括：\n";
        list = query("BAOXIANG_LIST", this_object());
        if(!list || !mapp(list) ) {
                return str;
        }
        key = keys(list);
        for(i=0;i<sizeof(key);i++) {
                ob = load_object(key[i]);
                if(ob) {
                        str += "\t"+ob->name()+"("+query("id",ob)+")\n";
                }
        }
        return str;


}

int do_test(string arg)
{
        object me,this;
        me = this_player();

        this = this_object();

        if( !arg ) return notify_fail("你要测试什么？\n"); 
        if(present(arg,environment()) != this) {
                return 0;
        }

        tell_object(me,test(me,this)+"\n");
        return 1;
}

string test(object me,object this)
{
        mixed list;
        string str;
        mixed keys;
        object ob;
        int totalRate;
        int i;

        str = this->name()+"\n";

        list = query("BAOXIANG_LIST", this);

        if(!list || !mapp(list)) {
                str += "上没有BAOXIANG_LIST属性，或者该属性不是mapping！";
        } else {
                keys = keys(list);
                if(!sizeof(keys)) {
                        str += "BAOXIANG_LIST列表为空！";
                } else {
                        totalRate = 0;
                        for(i=0;i<sizeof(keys);i++) {
                                totalRate += list[keys[i]];
                                ob = load_object(keys[i]);      
                                if(!ob) {
                                        str += keys[i]+"（概率："+list[keys[i]]+"）加载失败，可能无文件或文件编译错误\n";
                                } else {
                                        str += keys[i]+"["+ob->name()+"]"+"（概率："+list[keys[i]]+"）正常。\n";
                                }
                        }

                        if(totalRate == TOTALRATE) {
                                str += "总概率："+totalRate+"正常。";
                        } else {
                                str += "总概率："+totalRate+"不正常！！！！";
                        }
                }

        }
        return str;

}

int do_open(string arg)
{
        object me,this;
        me = this_player();
        this = this_object();
        if( !arg ) return notify_fail("你要打开什么？\n");
        if(present(arg,environment()) != this) {
                return 0;
        }
        if(this->query_amount()) {
                if(open_baoxiang(me,this)) {
                        this->add_amount(-1);
                        return 1;
                } else {
                        return 0;
                }
        } else {
                return 0;
        }
}

int open_baoxiang(object me,object this)
{
        mixed list;
        object ob;
        mixed keys;
        int totalRate;
        int rand;       
        int i;

        string str;

        list = query("BAOXIANG_LIST", this);
        
        if(!list || !mapp(list)) {
                return 0;
        }
        
        totalRate = 0;
        rand = random(TOTALRATE);       

        keys = keys(list);
        for(i=0;i<sizeof(list);i++) {
                if(rand >= totalRate && rand < totalRate+list[keys[i]]) {
                        ob = new(keys[i]);
                        if(ob && ob->move(me)) {
                                str = "打开了一个"+this->name()+"，从里边得到了"+ob->name()+"("+query("id",ob)+")。\n";
                                tell_room(environment(me),me->name()+str,({me}));
                                tell_object(me,"你"+str);
                                return 1;
                        } else {
                                if(ob) {
                                        tell_object(me,"打开"+this->name()+"失败了。\n");
                                        destruct(ob);
                                }
                                return 0;
                        }
                } else {
                        totalRate += list[keys[i]];
                }
        }
        return 0;
}

