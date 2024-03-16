#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  return this->closed_;
}

void Writer::push( string data )
{
  if ( !this->closed_ ) {
    uint64_t remian = this->capacity_ - this->buffer_.size();
    uint64_t to_push = min( remian, data.size() );
    this->buffer_ += data.substr( 0, to_push );
    this->write_bytes_ += to_push;
  }
  return;
}

void Writer::close()
{
  this->closed_ = true;
}

uint64_t Writer::available_capacity() const
{

  return this->capacity_ - this->buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return this->write_bytes_;
}

bool Reader::is_finished() const
{
  return this->closed_ && this->buffer_.size() == 0;
}

uint64_t Reader::bytes_popped() const
{
  return this->read_bytes_;
}

string_view Reader::peek() const
{
  return string_view( this->buffer_ );
}

void Reader::pop( uint64_t len )
{
  uint64_t to_pop = min( len, this->buffer_.size() );
  this->buffer_ = this->buffer_.substr( to_pop );
  this->read_bytes_ += to_pop;
}

uint64_t Reader::bytes_buffered() const
{
  return this->buffer_.size();
}
