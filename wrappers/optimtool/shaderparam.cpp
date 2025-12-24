#include <assert.h>
#include "shaderparam.h"



//---------------------------------------------------------------

bool isEqual(const std::shared_ptr<Param>& left, const std::shared_ptr<Param>& right)
{
    assert(left != nullptr && right != nullptr);
    if (left->GetParamType() != right->GetParamType())
    {
        return false;
    }
    if (left->GetParamType() == ParamType::FLOAT4)
    {
        std::shared_ptr <ParamFloat4> pl = std::static_pointer_cast<ParamFloat4>(left);
        std::shared_ptr <ParamFloat4> pr = std::static_pointer_cast<ParamFloat4>(right);
        return *pl == *pr;
    }
    else if (left->GetParamType() == ParamType::FLOATVEC)
    {
        std::shared_ptr <ParamFloatVec> pl = std::static_pointer_cast<ParamFloatVec>(left);
        std::shared_ptr <ParamFloatVec> pr = std::static_pointer_cast<ParamFloatVec>(right);
        return *pl == *pr;
    }
    else if (left->GetParamType() == ParamType::TEXTURE)
    {
        std::shared_ptr <ParamTexture> pl = std::static_pointer_cast<ParamTexture>(left);
        std::shared_ptr <ParamTexture> pr = std::static_pointer_cast<ParamTexture>(right);
        return *pl == *pr;
    }
    else if (left->GetParamType() == ParamType::BUFFER)
    {
        printf("isequal param buffer\n");
        std::shared_ptr <ParamBuffer> pl = std::static_pointer_cast<ParamBuffer>(left);
        std::shared_ptr <ParamBuffer> pr = std::static_pointer_cast<ParamBuffer>(right);
        return *pl == *pr;
    }
    return false;
}


bool isLess(const std::shared_ptr<Param>& left, const std::shared_ptr<Param>& right)
{
    assert(left != nullptr && right != nullptr);
    if (left->GetParamType() != right->GetParamType())
    {
        return left->GetParamType() < right->GetParamType();
    }
    if (left->GetParamType() == ParamType::FLOAT4)
    {
        std::shared_ptr <ParamFloat4> pl = std::static_pointer_cast<ParamFloat4>(left);
        std::shared_ptr <ParamFloat4> pr = std::static_pointer_cast<ParamFloat4>(right);
        return *pl < *pr;
    }
    else if (left->GetParamType() == ParamType::FLOATVEC)
    {
        std::shared_ptr <ParamFloatVec> pl = std::static_pointer_cast<ParamFloatVec>(left);
        std::shared_ptr <ParamFloatVec> pr = std::static_pointer_cast<ParamFloatVec>(right);
        return *pl < *pr;
    }
    else if (left->GetParamType() == ParamType::TEXTURE)
    {
        std::shared_ptr <ParamTexture> pl = std::static_pointer_cast<ParamTexture>(left);
        std::shared_ptr <ParamTexture> pr = std::static_pointer_cast<ParamTexture>(right);
        return *pl < *pr;
    }
    else if (left->GetParamType() == ParamType::BUFFER)
    {
        std::shared_ptr <ParamBuffer> pl = std::static_pointer_cast<ParamBuffer>(left);
        std::shared_ptr <ParamBuffer> pr = std::static_pointer_cast<ParamBuffer>(right);
        return *pl < *pr;
    }
    return false;
}
//---------------------------------------------------------------
ParamType ParamFloat4::sType = ParamType::FLOAT4;
ParamType ParamFloat4::GetParamType()
{
    return ParamFloat4::sType;
}

bool ParamFloat4::operator<(const ParamFloat4& other) const
{
    for (int i = 0; i < 4; i++)
    {
        if (m_Data[i] < other.m_Data[i])
        {
            return true;
        }
    }
    return false;
}

bool ParamFloat4::operator==(const ParamFloat4& other) const
{
    for (int i = 0; i < 4; i++)
    {
        if (m_Data[i] != other.m_Data[i])
        {
            return false;
        }
    }
    return true;
}

bool ParamFloat4::operator!=(const ParamFloat4& other) const
{
    return !(*this == other);
}
//---------------------------------------------------------------
ParamType ParamFloatVec::sType = ParamType::FLOATVEC;
ParamType ParamFloatVec::GetParamType()
{
    return  ParamFloatVec::sType;
}

bool ParamFloatVec::operator<(const ParamFloatVec& other) const
{
    if (m_Data.size() != other.m_Data.size())
    {
        return m_Data.size() < other.m_Data.size();
    }
    for (int i = 0; i < m_Data.size(); i++)
    {
        if (m_Data[i] < other.m_Data[i])
        {
            return true;
        }
    }
    return false;
}

bool ParamFloatVec::operator!=(const ParamFloatVec& other) const
{
    return !(*this == other);
}

bool ParamFloatVec::operator==(const ParamFloatVec& other) const
{
    if (m_Data.size() != other.m_Data.size())
    {
        return false;
    }
    for (int i = 0; i < m_Data.size(); i++)
    {
        if (m_Data[i] != other.m_Data[i])
        {
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------

ParamType ParamTexture::sType = ParamType::TEXTURE;
ParamType ParamTexture::GetParamType()
{
    return  ParamTexture::sType;
}

bool ParamTexture::operator<(const ParamTexture& other) const
{
    return m_TextureID < other.m_TextureID;
}

bool ParamTexture::operator==(const ParamTexture& other) const
{
    return m_TextureID == other.m_TextureID;
}

bool ParamTexture::operator!=(const ParamTexture& other) const
{
    return !(*this == other);
}

//---------------------------------------------------------------

ParamType ParamBuffer::sType =  ParamType::BUFFER;
ParamType ParamBuffer::GetParamType()
{
    return  ParamBuffer::sType;
}

bool ParamBuffer::operator<(const ParamBuffer& other) const
{
    return m_BufferID < other.m_BufferID;
}

bool ParamBuffer::operator!=(const ParamBuffer& other) const
{
    return !(*this == other);
}

bool ParamBuffer::operator==(const ParamBuffer& other) const
{
    printf("ParamBuffer::operator== %d ,%d\n", m_BufferID, other.m_BufferID);
    return m_BufferID == other.m_BufferID;
}


//---------------------------------------------------------------
ShaderParam::ShaderParam()
{

}

ShaderParam::~ShaderParam()
{

    m_SlotParamMap.clear();
}

int ShaderParam::SetParam(unsigned locate, const std::shared_ptr <Param>& value)
{
    printf("ShaderParam::SetParam %d\n",locate);
    if (m_SlotParamMap.find(locate)!= m_SlotParamMap.end())
    {
        if (isEqual(value, m_SlotParamMap[locate]))
        {
            printf("ShaderParam::SetParam ret1\n");
            return 1;
        }
    }
    
    m_SlotParamMap[locate] = value;
    printf("ShaderParam::SetParam END\n");
    return 0;
}


bool ShaderParam::operator<(const ShaderParam& other) const
{
    if (m_ProgramID != other.m_ProgramID)
    {
        return m_ProgramID < other.m_ProgramID;
    }
    if (m_SlotParamMap.size() != other.m_SlotParamMap.size())
    {
        return m_SlotParamMap.size() < other.m_SlotParamMap.size();
    }
    for (auto itr = m_SlotParamMap.begin(); itr != m_SlotParamMap.end(); itr++)
    {
        auto other_itr = other.m_SlotParamMap.find(itr->first);
        if (other_itr == other.m_SlotParamMap.end() || isLess(itr->second, other_itr->second))
        {
            return true;
        }
    }
    return false;
}

bool ShaderParam::operator==(const ShaderParam& other) const
{
    printf("ShaderParam::operator==\n");
    if (m_ProgramID != other.m_ProgramID)
    {
        return false;
    }
    if (m_SlotParamMap.size() != other.m_SlotParamMap.size())
    {
        return false;
    }
    
    for (auto itr = m_SlotParamMap.begin(); itr != m_SlotParamMap.end(); itr++)
    {
        printf("--ShaderParam::operator== key is  %d\n", itr->first);
        auto other_itr = other.m_SlotParamMap.find(itr->first);
        if (other_itr == other.m_SlotParamMap.end() || !isEqual(itr->second, other_itr->second))
        {
            return false;
        }
    }
    return true;
}

bool ShaderParam::operator!=(const ShaderParam& other) const
{
    return !(*this == other);
}


