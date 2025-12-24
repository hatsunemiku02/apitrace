#pragma once
#include <map>
#include <vector>
#include <memory>

enum ParamType
{
    UNKNOWN = 0,
    TEXTURE,
    BUFFER,
    FLOAT4,
    FLOATVEC,
};

class Param
{
public:
   
    Param()
    {

    }
    virtual ~Param()
    {

    }
    virtual ParamType GetParamType()
    {
        return ParamType::UNKNOWN;
    }
    bool operator<(const Param& other) const
    {

    }
    bool operator==(const Param& other) const
    {

    }
    bool operator!=(const Param& other) const
    {

    }
protected:
private:
};

class ParamFloat4 :public Param
{
public:
    static ParamType sType;
    virtual ParamType GetParamType();

public:
    ParamFloat4(float* data)
    {
        for (int i=0;i<4;i++)
        {
            m_Data[i] = data[i];
        }
    }
    virtual ~ParamFloat4()
    {

    }
    bool operator<(const ParamFloat4& other) const;
    bool operator==(const ParamFloat4& other) const;
    bool operator!=(const ParamFloat4& other) const;
protected:
private:
    float m_Data[4];
};

class ParamFloatVec :public Param
{
public:
    static ParamType sType;
    virtual ParamType GetParamType();

public:
    ParamFloatVec(float* data,unsigned size)
    {
        m_Data.resize(size);
        for (int i = 0; i < 4; i++)
        {
            m_Data[i] = data[i];
        }
    }
    virtual ~ParamFloatVec()
    {

    }
    bool operator<(const ParamFloatVec& other) const;
    bool operator==(const ParamFloatVec& other) const;
    bool operator!=(const ParamFloatVec& other) const;
protected:
private:
    std::vector<float> m_Data;
};

class ParamTexture :public Param
{
public:
    static ParamType sType;
    virtual ParamType GetParamType();
public:
    ParamTexture(unsigned id)
        :m_TextureID(id)
    {

    }
    virtual ~ParamTexture()
    {

    }
    bool operator<(const ParamTexture& other) const;
    bool operator==(const ParamTexture& other) const;
    bool operator!=(const ParamTexture& other) const;
protected:
private:
    unsigned m_TextureID;
};

class ParamBuffer :public Param
{
public:
    static ParamType sType;
    virtual ParamType GetParamType();
public:
    ParamBuffer(unsigned id)
        :m_BufferID(id)
    {
        printf("ParamBuffer::ParamBuffer %d\n",m_BufferID);
    }
    ~ParamBuffer()
    {
        printf("ParamBuffer::~ParamBuffer %d\n", m_BufferID);
    }
    unsigned GetBufferID()
    {
        return m_BufferID;
    }

    bool operator<(const ParamBuffer& other) const;
    bool operator==(const ParamBuffer& other) const;
    bool operator!=(const ParamBuffer& other) const;
protected:
private:
    unsigned m_BufferID;
};

bool isEqual(const std::shared_ptr<Param>& left, const std::shared_ptr<Param>& right);
bool isLess(const std::shared_ptr<Param>& left, const std::shared_ptr<Param>& right);

class ShaderParam
{
public:
    ShaderParam();
    ShaderParam(unsigned pg)
        :m_ProgramID(pg)
        ,m_SlotParamMap()
    {

    }

    virtual ~ShaderParam();
    int SetParam(unsigned locate,const std::shared_ptr <Param>& value);

    const std::map<unsigned, std::shared_ptr<Param>>& GetSlotParamMap() const
    {
        return m_SlotParamMap;
    }
    bool operator<(const ShaderParam& other) const;
    bool operator==(const ShaderParam& other) const;
    bool operator!=(const ShaderParam& other) const;
private:
    unsigned m_ProgramID;
    std::map<unsigned, std::shared_ptr<Param>> m_SlotParamMap;
};