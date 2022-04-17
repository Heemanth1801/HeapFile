#include<bits/stdc++.h>
using namespace std;
int page_size;

class record{
    public:
        record(int a,int b){
            size=a;
            primary_key=b;
            slot_id=0;
        }
        int get_primarykey(){
            return primary_key;
        }
        int get_size(){
            return size;
        }
        int get_slotid(){
            return slot_id;
        }
        void put_slotid(int a){
            slot_id=a;
        }
    private:
        int primary_key;
        int size;
        int slot_id;
};

class page{
    public:
        page(){
            count=0;
            left=nullptr;
            right=nullptr;
            page_id=0;
            present_address=0;
            space=page_size-16;
        }
        page* get_left(){
            return left;
        }
        page* get_right(){
            return right;
        }
        record* get_record(int index){
            if(index>=count){
                return nullptr;
            }
            else{
                return directory[index];
            }
        }
        void put_record(record* a){
            directory.push_back(a);
            present_address++;
        }
        int get_count(){
            return count;
        }
        int get_pageid(){
            return page_id;
        }
        int get_space(){
            return space;
        }
        void decrease_space(int a){
            space=space-a;
        }
        void put_pageid(int a){
            page_id=a;
        }
        void put_left(page* a){
            left=a;
        }
        void put_right(page* a){
            right=a;
        }
        void increase_count(){
            count++;
        }
        void decrease_count(){
            count--;
        }
    private:
        int count;
        int page_id;
        int space;
        page* left;
        page* right;
        int present_address;
        vector<record*> directory;
};

class heapfile{
    public:
        heapfile(){
            count=0;
            head=nullptr;
        }
        int get_count(){
            return count;
        }
        void increase_count(){
            count++;
        }
        page* get_head(){
            return head;
        }
        void put_head(page* a){
            head=a;
        }
    private:
        int count;
        page* head;
};

void printing(){
    cout<<"testing..."<<endl;
}

void insertion(heapfile* file,page*left_page,page*head,int key,int size){
    if(head==nullptr){
        record* temp=new record(size,key);
        page* buff = new page();
        file->increase_count();
        if(left_page!=nullptr){
            buff->put_pageid(left_page->get_pageid()+1);
        }
        else{
            file->put_head(buff);
        }
        buff->increase_count();
        buff->put_record(temp);
        buff->decrease_space(size+4);
        buff->put_left(left_page);
        buff->put_right(nullptr);
        if(left_page!=nullptr){
            left_page->put_right(buff);
        }
        return;
    }
    else if(head->get_space()>=size+4){
        record* temp=new record(size,key);
        temp->put_slotid((head->get_record((head->get_count()-1))[0].get_slotid())+1);
        head->put_record(temp);
        head->increase_count();
        head->decrease_space(size+4);
        return;
    }
    else{
        insertion(file,head,head->get_right(),key,size);
        return;
    }
}

void search(page* head,int primary_key){
    int i,j;
    j=0;
    while(head!=nullptr){
        for(i=0;i<head->get_count();i++){
            if((head->get_record(i))[0].get_primarykey()==primary_key){
            j=1;
            cout<<head->get_pageid()<<" "<<i<<endl;
            }
        }
        head=head->get_right();
    }
    if(j==0){
        cout<<-1<<" "<<-1<<endl;
    }
}

void displaying_status(heapfile* file,page* head){
    
    cout<<file->get_count()<<" ";

    while(head!=nullptr){
        cout<<head->get_count()<<" ";
        head=head->get_right();
    }
    cout<<endl;
}

int main(){
    cin>>page_size;
    int code,key,size;
    page* head=nullptr;
    heapfile* file=new heapfile();
    while(1){
        cin>>code;
        switch(code){
            case 1:cin>>size>>key;insertion(file,nullptr,head,key,size);
                head=file->get_head();
                break;
            case 2:displaying_status(file,head);break;
            case 3:cin>>key;search(head,key);break;
            case 4:return 0;
        }
    }
    return 0;
}