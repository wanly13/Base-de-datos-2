#include <iostream>

struct Bucket{
    Record records[4];
    long next;
    int count = 0;
}

//Algoritmo de Inserción

void insert (Record record){
    file open (“data.dat”);
    key_hash = hash_code(record.data);  
    seek(key_hash * sizeof(Bucket));

    Bucket bucket;
    read ((char*)&bucket, sizeof(Bucket));

    if (bucket.count < 4){
        bucket.records [bucket.count] = record;
        bucket.count++;
        seek(key_hash * sizeof(Bucket));
        write ((char*)&bucket, sizeof(Bucket));
    }

    else{  //Recorrido por overflow
        while (bucket.next!=-1){
            pos_last_bucket = bucket.next;
            seek (bucket.next);
            read ((char*)&bucket, sizeof(Bucket));
        }
        if (bucket.count < 4){
            bucket.records [bucket.count] = record;
            bucket.count++;
            seek(pos_last_bucket);
            write ((char*)&bucket, sizeof(Bucket));
        }

        else {
            Bucket NewBucket
            bucket.next = file.tellg();
            NewBucket.records [NewBucket.count] = record;
            NewBucket.count++;
            NewBucket.next = -1;
            write ((char*)&NewBucket, sizeof(Bucket));
        }

    }
}

//Algortimo de Búsqueda


Record search(Record record){
    open ("data.dat");
    key_hash = hash_code(record.data);
    seek(key_hash * sizeof(Bucket))

    Bucket bucket;
    read ((char*)&bucket, sizeof(Bucket));

    bool flag = 0;

    for (auto &v : bucket.records){
        if (v == record.data) {
            flag = 1;
            return v;
        }
    }

    //Recorrido por el overflow
    while (bucket.next!=-1){
        seek (bucket.next);
        read ((char*)&bucket, sizeof(Bucket));
        for (auto &v : bucket.records){
            if (v = record.data) {
                flag = 1;
                return v;
            }
        }
    }

    if (flag == 0){
        throw ("El registro no existe");
    }
}